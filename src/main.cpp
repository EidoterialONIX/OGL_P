#include "Eidor/Eidor.cpp"

#include <iostream>
#include <vector>
#include <math.h>


const char* vertex = 
"#version 140\n"
"in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragment =
"#version 140\n"
"out vec4 FragColor;"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"}\n";



class Shader_Program {
private:

    GLuint _shader_program = 0;
 
    void Check_Correct_Compile(GLuint id, const char* type) {
        
        int success = 0;
        char log[512];

        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(id, 512, NULL, log);
            std::cout << type << log << std::endl;

        }

    }
    void Check_Correct_Link() {

        int success = 0;
        char log[512];

        glGetProgramiv(_shader_program, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(_shader_program, 512, NULL, log);
            std::cout << "Linker\n" << log << std::endl;

        }

    }
    

public:

    Shader_Program(const char* vertex_shader, const char* fragment_shader) {

        GLuint vertex_sh = 0;
        vertex_sh = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertex_sh, 1, &vertex_shader, NULL);
        glCompileShader(vertex_sh);
        Check_Correct_Compile(vertex_sh, "Vertex\n");

        GLuint fragment_sh = 0;
        fragment_sh = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragment_sh, 1, &fragment_shader, NULL);
        glCompileShader(fragment_sh);
        Check_Correct_Compile(fragment_sh, "Fragment\n");

        _shader_program = glCreateProgram();

        glAttachShader(_shader_program, vertex_sh);
        glAttachShader(_shader_program, fragment_sh);
        glLinkProgram(_shader_program);
        Check_Correct_Link();

        glDeleteShader(vertex_sh);
        glDeleteShader(fragment_sh);

    }

    void USE() { glUseProgram(_shader_program); }



};





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

    void set_Scale(Vector_3<float> scale) { _scale = scale; }

    void change_Rotate(int rotate) { if (_rotate == 360) _rotate = 0; else _rotate += rotate; }

    void TRANSFORM_SCALE(Primitive& primitive) {
        primitive *= Primitive(_scale, _scale, _scale);
    }

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

    float _color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

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
    Vector_3<float>* get_Points() { return _points; }

    void set_Color(float red, float green, float blue, float alpha) { _color[0] = red; _color[1] = green; _color[2] = blue; _color[3] = alpha; };
    float* get_Color() { return _color; }
};


class Draw_on_screen {

    GLuint VBO = 0;
    GLuint VAO = 0;

    Primitive _primitive;

    GLfloat _cordinat[9];


public:
   
    Draw_on_screen() = default;

    void Draw(Rect RECT, Shader_Program shader_program) {

        for (int i{ 0 }; i < RECT.get_Count_Point() - 2; i++) {

            _primitive = Primitive(RECT.get_Point(0), RECT.get_Point(1 + i), RECT.get_Point(2 + i));

            RECT.TRANSFORM_SCALE(_primitive);
            RECT.CONVERT_CORDINAT(_primitive, _cordinat, _options);

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);


            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(_cordinat), _cordinat, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindVertexArray(0);

            shader_program.USE();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

        }

    }

};

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

    Rect rect;

    rect.set_Position(Vector_3<float>(50.0f, 100.0f, 0.0f));
    rect.set_Size(Vector_3<float>(100.0f, 200.0f, 0.0f));


    Shader_Program shader(vertex, fragment);
    
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        Drawinger.Draw(rect, shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}