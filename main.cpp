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
#include "object3d.h"
#include "window.h"
#include "engine.h"
#include "triangle.h"

namespace ch = std::chrono;

using WndPtr = GLFWwindow*;

int main()
{
    system("clear");

    vertex_t vert_1 = std::make_shared<glm::vec3>(glm::vec3(-0.5f, -0.5f, 0.0f));
    vertex_t vert_2 = std::make_shared<glm::vec3>(glm::vec3(0.5f, -0.5f, 0.0f));
    vertex_t vert_3 = std::make_shared<glm::vec3>(glm::vec3(0.0f, 0.5f, 0.0f));
    

    Triangle tr1 (vert_1, vert_2, vert_3);
    
    Object3D* tr = &tr1;

    Engine::engine().run(tr);

    // Window window(4.6f, "Visual Engine");

    // auto time_start = ch::high_resolution_clock().now();    

    // GLfloat vertices[] = {
    //     -0.5f, -0.5f, 0.0f,
    //      0.5f, -0.5f, 0.0f,
    //      0.0f,  0.5f, 0.0f
    // };

    // // ShaderTree::get().initShaderTree("shaders");

    // // std::cout << glfwGetVersionString() << '\n';
    // // std::cout << glewGetString(GLEW_VERSION) << "\n\n";

    // if (!glfwInit())
    // {
    //     std::cout << "|    EROR     | initialize GLFW\n" << "|             | " << glGetError() << '\n';
    //     return -1;
    // }
    // std::cout << "| SUCCSESSFUL | initialize GLFW\n";

	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // WndPtr window = glfwCreateWindow(1366, 768, "VisualEngine", nullptr, nullptr);

    // if (window == nullptr)
    // {
    // 	std::cout << "|    EROR     | Window create\n";
    // 	glfwTerminate();
    // 	return -1;
    // }
    // std::cout << "| SUCCSESSFUL | Window create\n";

    // glfwMakeContextCurrent(window);

    // glewExperimental = GL_TRUE;
    // if (auto err =glewInit(); err != GLEW_OK)
    // {
    //     std::cout << "|    EROR     | initialize GLEW\n" << "|             | " << glewGetErrorString(err) << '\n' << "|             | " << glGetError() << '\n';
    //     // return -1;
    // }
    // std::cout << "| SUCCSESSFUL | Initialize GLEW\n";

    // int width, height;
    // glfwGetFramebufferSize(window, &width, &height);

    // glViewport(0, 0, width, height);

    // VertexShader vertex(GL_VERTEX_SHADER);
    // FragmentShader frag(GL_FRAGMENT_SHADER);

    // vertex.addSource(loadShaderFromFile("shaders/primitive/primitive.vert.glsl"));
    // frag.addSource(loadShaderFromFile("shaders/primitive/primitive.frag.glsl"));

    // ShaderProgram shader;
   
    // shader.attachShader(vertex);
    // shader.attachShader(frag);

    // shader.link();

    // // GLint color = glGetUniformLocation(shader.getID(), "Color");
    

    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);

    // glfwTerminate();
    // std::cout << "|    INFO     | resource clear\n";
    // std::cout << "|    INFO     | Work session end\n";

	return 0;
}
