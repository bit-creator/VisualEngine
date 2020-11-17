#include <iostream>
#include <chrono>
#include <cmath>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

// #include "ShaderProgram.hpp"
#include "globject.hpp"
#include "shader.h"
#include "shaderprogram.h"
// #include "shadertree.h"

namespace ch = std::chrono;

using WndPtr = GLFWwindow*;

int main()
{
    system("clear");

    auto time_start = ch::high_resolution_clock().now();    

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // ShaderTree::get().initShaderTree("shaders");

    // std::cout << glfwGetVersionString() << '\n';
    // std::cout << glewGetString(GLEW_VERSION) << "\n\n";

    if (!glfwInit())
    {
        std::cout << "|    EROR     | initialize GLFW\n" << "|             | " << glGetError() << '\n';
        return -1;
    }
    std::cout << "| SUCCSESSFUL | initialize GLFW\n";

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    WndPtr window = glfwCreateWindow(1366, 768, "VisualEngine", nullptr, nullptr);

    if (window == nullptr)
    {
    	std::cout << "|    EROR     | Window create\n";
    	glfwTerminate();
    	return -1;
    }
    std::cout << "| SUCCSESSFUL | Window create\n";

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (auto err =glewInit(); err != GLEW_OK)
    {
        std::cout << "|    EROR     | initialize GLEW\n" << "|             | " << glewGetErrorString(err) << '\n' << "|             | " << glGetError() << '\n';
        // return -1;
    }
    std::cout << "| SUCCSESSFUL | Initialize GLEW\n";

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);

    VertexShader vertex(GL_VERTEX_SHADER);
    FragmentShader frag(GL_FRAGMENT_SHADER);

    vertex.addSource(loadShaderFromFile("shaders/primitive/primitive.vert.glsl"));
    frag.addSource(loadShaderFromFile("shaders/primitive/primitive.frag.glsl"));

    ShaderProgram shader;
   
    shader.attachShader(vertex);
    shader.attachShader(frag);

    shader.link();

    // GLint color = glGetUniformLocation(shader.getID(), "Color");
    
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.enable();

        auto current_time = ch::high_resolution_clock().now();    
        auto count = duration_cast<ch::milliseconds>(current_time - time_start).count();

        float f1 = std::abs(std::sin(1 * count));
        float f2 = std::abs(std::sin(2 * count));
        float f3 = std::abs(std::sin(3 * count));

        shader.setUniform("Color", f1, f2, f3, 1.0);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    std::cout << "|    INFO     | resource clear\n";
    std::cout << "|    INFO     | Work session end\n";

	return 0;
}
