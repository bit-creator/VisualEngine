#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

using WndPtr = GLFWwindow*;

int execute(WndPtr window);

int main()
{
    system("clear");

	glfwInit();

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
    if (glewInit() != GLEW_OK)
    {
        std::cout << "|    EROR     | initialize GLEW\n";
        return -1;
    }
    std::cout << "| SUCCSESSFUL | Initialize GLEW\n";

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);

	return execute(window);
}

int execute(WndPtr window)
{
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    std::cout << "|    INFO     | resource clear\n";
    std::cout << "|    INFO     | Work session end\n";

    return 0;
}
