#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include<math.h>


template <class T>
class Vec_3 {
public:

    T _x = 0;
    T _y = 0;
    T _z = 0;

    Vec_3() = default;

    Vec_3(T x, T y, T z) : _x(x), _y(y), _z(z) {}

    void operator=(Vec_3<T> v) { _x = v._x; _y = v._y; _z = v._z; }

};

class Point_3 {
public:
    GLfloat _point[9];

    Point_3() = default;

    Point_3(Vec_3<float> v0, Vec_3<float> v1, Vec_3<float> v2) {

        _point[0] = v0._x; _point[1] = v0._y; _point[2] = v0._z;
        _point[3] = v1._x; _point[4] = v1._y; _point[5] = v1._z;
        _point[6] = v2._x; _point[7] = v2._y; _point[8] = v2._z;

    };

    void operator=(Point_3 p) {

        _point[0] = p._point[0]; _point[1] = p._point[1]; _point[2] = p._point[2];
        _point[3] = p._point[3]; _point[4] = p._point[4]; _point[5] = p._point[5];
        _point[6] = p._point[6]; _point[7] = p._point[7]; _point[8] = p._point[8];

    }

    void operator+=(Point_3 p) {
        _point[0] += p._point[0]; _point[1] += p._point[1]; _point[2] += p._point[2];
        _point[3] += p._point[3]; _point[4] += p._point[4]; _point[5] += p._point[5];
        _point[6] += p._point[6]; _point[7] += p._point[7]; _point[8] += p._point[8];
    }

};


class Trilangl {
private:

    Vec_3<float> _position = Vec_3<float>(0.0f, 0.0f, 0.0f);

    Point_3 _points;


public:


    Trilangl() = default;

    void set_Points(Point_3 points) {

        points += Point_3(_position, _position, _position); 

        _points = points;

    }

    void set_Position(Vec_3<float> position) { _position = position; }


    Point_3& get_Points() { return _points; }


};






class Draw_on_screen {
public:
   
    Draw_on_screen() {}
    
    void DRAW_TRILANGL(Trilangl& TRILANGL) {
        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(TRILANGL.get_Points()._point), TRILANGL.get_Points()._point, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glDrawArrays(GL_TRIANGLES, 0, 3);

    }

};




class bg {
public:

    const GLfloat _r[4]{1.0f, 0.0f, 0.0f, 1.0f};
    const GLfloat _g[4]{ 0.0f, 1.0f, 0.0f, 1.0f };
    const GLfloat _b[4]{ 0.0f, 0.0f, 1.0f, 1.0f };

    bg() {}

};
bg a;


int g_windowSizeX = 640;
int g_windowSizeY = 480;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
    else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        glClearColor(a._r[0], a._r[1], a._r[2], a._r[3]);
    }
    else if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        glClearColor(a._g[0], a._g[1], a._g[2], a._g[3]);
    }
    else if (key == GLFW_KEY_B && action == GLFW_PRESS) {
        glClearColor(a._b[0], a._b[1], a._b[2], a._b[3]);
    }
}



Trilangl tril1;


Draw_on_screen Drawinger;



int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "OGL_P", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD!" << std::endl;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(1, 1, 0, 1);


    tril1.set_Position(Vec_3<float>(-0.5f, 0.5f, 0.0f));

    tril1.set_Points(Point_3(Vec_3<float>(0.5f, 0.5f, 0.0f), Vec_3<float>(-0.5f, 0.5f, 0.0f), Vec_3<float>(-0.5f, -0.5f, 0.0f)));
    
   

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        Drawinger.DRAW_TRILANGL(tril1);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}