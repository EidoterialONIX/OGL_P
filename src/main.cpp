#include "Eidor/Eidor.cpp"

#include <iostream>
#include <vector>
#include <math.h>


struct Options {

    int WINDOW_SIZE[2] = { 640, 480 };


};


Options _options;


class Transform {
private:
    
    Vector_3<float> _scale = Vector_3<float>(1.0f, 1.0f, 1.0f);

    int _rotate = 0;


public:

    Transform() = default;

    void TRANSFORM_SCALE(Primitive& primitive) {
        primitive *= Primitive(_scale, _scale, _scale);
    }

    void TRANSFORM_ROTATE(Primitive& primitive);

    void CONVERT_CORDINAT(Primitive primitive, GLfloat* cordinat, Options option) {

        for (int i{ 0 }; i < 3; i++) {
            cordinat[i * 3] = (primitive.get_Point(i)._x / (option.WINDOW_SIZE[0] / 2.0f / 100.0f) - 100) / 100.0f;
            cordinat[1 + i * 3] = -(primitive.get_Point(i)._y / (option.WINDOW_SIZE[1] / 2.0f / 100.0f) - 100) / 100.0f;

        }

    }

};

class Rect : public Transform {
private:

    Vector_3<float> _position;

    Vector_3<float> _size;

    int _count_point = 4;

    Vector_3<float> _points[4];

    Vector_3<float> _origin;

    void _Update() {

        _points[0] = _position;
        _points[1] = _position + Vector_3<float>(_size._x, 0.0f, 0.0f);
        _points[2] = _position + _size;
        _points[3] = _position + Vector_3<float>(0.0f, _size._y, 0.0f);

    }

public:

    Rect() {
        
        _position = Vector_3<float>(0.0f, 0.0f, 0.0f);

        _size = Vector_3<float>(0.0f, 0.0f, 0.0f);

        _origin = Vector_3<float>(0.0f, 0.0f, 0.0f);
        
        _Update();

    };

    Vector_3<float> get_Position() const { return _position; }
    void set_Position(Vector_3<float> position) { _position = position; _Update(); }

    Vector_3<float> get_Size() const { return _size; }
    void set_Size(Vector_3<float> size) { _size = size; _Update(); }

    int get_Count_Point() const { return _count_point; }

    Vector_3<float> get_Point(int index) const { return _points[index]; }

};





class Draw_on_screen {

    Primitive _primitive;

    GLfloat _cordinat[9];


public:
   
    Draw_on_screen() = default;

    void Draw(Rect& RECT) {

        for (int i{ 0 }; i < RECT.get_Count_Point() - 2; i++) {

            _primitive = Primitive(RECT.get_Point(0), RECT.get_Point(1 + i), RECT.get_Point(2 + i));

            RECT.TRANSFORM_SCALE(_primitive);
            ///RECT.TRANSFORM_ROTATE(_primitive);
            RECT.CONVERT_CORDINAT(_primitive, _cordinat, _options);


            GLuint points_vbo = 0;
            glGenBuffers(1, &points_vbo);

            glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(_cordinat), _cordinat, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

            glDrawArrays(GL_TRIANGLES, 0, 3);

        }

    }

};


class bg {
public:

    const GLfloat _r[4]{1.0f, 1.0f, 0.0f, 1.0f};
    const GLfloat _g[4]{ 0.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat _b[4]{ 1.0f, 0.0f, 1.0f, 1.0f };

    bg() {}

};
bg a;


Rect rect;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    _options.WINDOW_SIZE[0] = width;
    _options.WINDOW_SIZE[1] = height;
    glViewport(0, 0, _options.WINDOW_SIZE[0], _options.WINDOW_SIZE[1]);
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
    else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        rect.set_Position(rect.get_Position() + Vector_3<float>(3.0f, 0.0f, 0.0f));
    }
}

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
    GLFWwindow* pWindow = glfwCreateWindow(_options.WINDOW_SIZE[0], _options.WINDOW_SIZE[1], "OGL_P", nullptr, nullptr);
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


    rect.set_Position(Vector_3<float>(100.0f, 200.0f, 0.0f));
    rect.set_Size(Vector_3<float>(150.0f, 100.0f, 0.0f));



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        Drawinger.Draw(rect);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}