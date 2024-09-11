#include "Eidor/Eidor.cpp"

#include <iostream>
#include <vector>
#include <math.h>


struct Options {

    int WINDOW_SIZE[2] = { 640, 480 };


};


Options _options;

class Primitive {
private:

    Point_3 _real_cordinat = Point_3(Vector_3<float>(0.0f, 0.0f, 0.0f), Vector_3<float>(0.0f, 0.0f, 0.0f), Vector_3<float>(0.0f, 0.0f, 0.0f));

    Point_3 _transform_cordinat = Point_3(Vector_3<float>(0.0f, 0.0f, 0.0f), Vector_3<float>(0.0f, 0.0f, 0.0f), Vector_3<float>(0.0f, 0.0f, 0.0f));

public:

    Primitive() = default;

    Point_3 get_Real_Cordinat() const { return _real_cordinat; }

    Point_3 get_Transform_Cordinat() const { return _transform_cordinat; }
    
    void _Show_Information_Real_Cordinat();

    void _Show_Information_Transform_Cordinat();

};

class Transform {
private:

    

    Vector_3<float> _position;
    float _scale = 1;

public:

    Transform() = default;

    Vec_3<float> get_Position() const { return _position; }
    void set_Position(Vec_3<float> new_position) { _position = new_position; }

    float get_Scale() const { return _scale; }
    void set_Scale(float new_scale) { _scale = new_scale; }

    void TRANSFORM_POSITION(Ordinary_Geometry &o_g) const {
        for (int i{ 0 }; i < 3; i++) {
            o_g.get_Points()._point[i * 3] = _position._x;
            o_g.get_Points()._point[1 + i * 3] = _position._y;
            o_g.get_Points()._point[2 + i * 3] = _position._z;
        }
        
    }

    void TRANSFORM_SCALE(Ordinary_Geometry& o_g) const {
        for (int i{ 0 }; i < 3; i++) {
            o_g.get_Points()._point[i * 3] *= _scale;
            o_g.get_Points()._point[1 + i * 3] *= _scale;
            o_g.get_Points()._point[2 + i * 3] *= _scale;
        }

    }

    void TRANSFORM_POINTS(Ordinary_Geometry& o_g, Options options) {
        Point_3 new_points = Point_3(Vec_3<float>(0.0f, 0.0f, 0.0f), Vec_3<float>(0.0f, 0.0f, 0.0f), Vec_3<float>(0.0f, 0.0f, 0.0f));

        for (int i{ 0 }; i < 3; i++) {

            new_points._point[i * 3] = (o_g.get_Points()._point[i * 3] / (options.WINDOW_SIZE[0] / 2.0f / 100.0f) - 100) / 100.0f;
            
            new_points._point[1 + i * 3] = -(o_g.get_Points()._point[1 + i * 3] / (options.WINDOW_SIZE[1] / 2.0f / 100.0f) - 100) / 100.0f;
        }

        o_g.set_Points_Transform(new_points);

    }
};


class Trilangl : public Transform {
private:

    float _radius = 0.0f;
    Ordinary_Geometry _figur;


public:

    Trilangl() = default;

    float get_Radius() const { return _radius; }
    void set_Radius(float new_radius) { _radius = new_radius; }

    void set_Trilangl() {
        TRANSFORM_POSITION(_figur);

        _figur.get_Points()._point[1] -= _radius;

        _figur.get_Points()._point[3] -= (_radius / 90) * 45;
        _figur.get_Points()._point[4] += (_radius / 90) * 45;

        _figur.get_Points()._point[6] += (_radius / 90) * 45;
        _figur.get_Points()._point[7] += (_radius / 90) * 45;

        std::cout << (_radius / 90) * 45 << std::endl;

        TRANSFORM_SCALE(_figur);

        TRANSFORM_POINTS(_figur, _options);
        
    }


    Ordinary_Geometry& get_Ordinary_Geometry() { return _figur; }

};


class Rect : public Transform {
private:

    Vec_3<float> _size = Vec_3<float>(0.0f, 0.0f, 0.0f);

    Ordinary_Geometry _figur[2];

public:

    Rect() = default;

    Vec_3<float> get_Size() const { return _size; }
    void set_Size(Vec_3<float> new_size) { _size = new_size; }

    void set_Rect() {
        TRANSFORM_POSITION(_figur[0]);
        TRANSFORM_POSITION(_figur[1]);

        /// First figur
        _figur[0].get_Points()._point[3] += _size._x;
        _figur[0].get_Points()._point[4] += _size._y;

        _figur[0].get_Points()._point[7] += _size._y;

        /// Second figur
        _figur[1].get_Points()._point[3] += _size._x;

        _figur[1].get_Points()._point[6] += _size._x;
        _figur[1].get_Points()._point[7] += _size._y;

        TRANSFORM_SCALE(_figur[0]);
        TRANSFORM_SCALE(_figur[1]);

        TRANSFORM_POINTS(_figur[0], _options);
        TRANSFORM_POINTS(_figur[1], _options);

    }

    Ordinary_Geometry& get_Ordinary_Geometry(int index) { return _figur[index]; }

};

class Draw_on_screen {
public:
   
    Draw_on_screen() {}
    
    void DRAW_TRILANGL(Trilangl& TRILANGL) {
        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);

        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(TRILANGL.get_Ordinary_Geometry().get_Points_Transform()._point), TRILANGL.get_Ordinary_Geometry().get_Points_Transform()._point, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glDrawArrays(GL_TRIANGLES, 0, 3);

    }

    void DRAW_RECT(Rect& RECT) {
        for (int i{ 0 }; i < 2; i++) {

            GLuint points_vbo = 0;
            glGenBuffers(1, &points_vbo);

            glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(RECT.get_Ordinary_Geometry(i).get_Points_Transform()._point), RECT.get_Ordinary_Geometry(i).get_Points_Transform()._point, GL_STATIC_DRAW);

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
}

Draw_on_screen Drawinger;

Trilangl tril;
Rect rect;

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

    tril.set_Radius(100.0f);
    tril.set_Position(Vec_3<float>(0.0f, 0.0f, 0.0f));

    tril.set_Trilangl();

    tril.get_Ordinary_Geometry().show_Info_Points();


    rect.set_Position(Vec_3<float>(0.0f, 0.0f, 0.0f));
    rect.set_Size(Vec_3<float>(100.0f, 100.0f, 0.0f));
    rect.set_Scale(1.4f);

    rect.set_Rect();


   

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        Drawinger.DRAW_RECT(rect);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}