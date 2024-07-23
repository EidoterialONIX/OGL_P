#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

class Point_3 {
public:
    GLfloat point[9];

    Point_3() = default;

    Point_3(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8) {
        point[0] = p0; point[1] = p1; point[2] = p2;
        point[3] = p3; point[4] = p4; point[5] = p5;
        point[6] = p6; point[7] = p7; point[8] = p8;

    };

};


class Vertex_Point_Bufer {
private:

    std::vector<Point_3> _vpb;


public:

    Vertex_Point_Bufer() {}


    void PUSH_VP(Point_3 p) {

        _vpb.resize(_vpb.size() + 1);
        
        _vpb[_vpb.size() - 1].point[0] = p.point[0]; _vpb[_vpb.size() - 1].point[1] = p.point[1]; _vpb[_vpb.size() - 1].point[2] = p.point[2];
        _vpb[_vpb.size() - 1].point[3] = p.point[3]; _vpb[_vpb.size() - 1].point[4] = p.point[4]; _vpb[_vpb.size() - 1].point[5] = p.point[5];
        _vpb[_vpb.size() - 1].point[6] = p.point[6]; _vpb[_vpb.size() - 1].point[7] = p.point[7]; _vpb[_vpb.size() - 1].point[8] = p.point[8];

    }


    void Resp(int index) {
        std::cout << "Lenght array: " << _vpb.size() << std::endl;

        for (int i{ 0 }; i < 9; i++) {
            std::cout << sizeof(_vpb[index]) << std::endl;
        }

    }

    std::vector<Point_3>& get_VPB() { return _vpb; }

};


class Draw_on_screen {
private:

    Vertex_Point_Bufer VPB;

public:
    

    Draw_on_screen() {}
    
    void Draw_VPB() {
        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);

        for (int i{ 0 }; i < VPB.get_VPB().size(); i++) {
            glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(VPB.get_VPB()[i]), &VPB.get_VPB()[i], GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

            glDrawArrays(GL_TRIANGLES, 0, 3);

        }

    }
    
    Vertex_Point_Bufer& get_VPB() { return VPB; }

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


Draw_on_screen Drawinger;

Point_3 points(0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f);


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


    Drawinger.get_VPB().PUSH_VP(points);

    Drawinger.get_VPB().Resp(0);

    /*
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, nullptr);
    glCompileShader(fs);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);
    glLinkProgram(shader_program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    */

   

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        Drawinger.Draw_VPB();

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}