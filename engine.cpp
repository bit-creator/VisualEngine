#include "engine.h"

Engine& Engine::engine() noexcept
{ static Engine engine; return engine; }

void Engine::addEventListener(EventPointer event)
{
    _eventListener = event;
}

void Engine::run(const Object3D* tr, const Window& window) noexcept
{
    VertexShader vertex(GL_VERTEX_SHADER);
    FragmentShader frag(GL_FRAGMENT_SHADER);

    vertex.addSource(loadShaderFromFile("shaders/primitive/primitive.vert.glsl"));
    frag.addSource(loadShaderFromFile("shaders/primitive/primitive.frag.glsl"));

    ShaderProgram shader;
   
    shader.attachShader(vertex);
    shader.attachShader(frag);

    shader.link();

    while (!glfwWindowShouldClose(window))
    {
        if(_eventListener) _eventListener -> onRender();

        glfwPollEvents();

        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        tr->render(shader);

        glfwSwapBuffers(window);
    }
}