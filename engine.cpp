#include "engine.h"

Engine& Engine::engine() noexcept
{ static Engine engine; return engine; }

void Engine::addEventListener(EventPointer eventListener)
{
    _eventListener = eventListener;
}

void Engine::setScene(ScenePtr scene) noexcept
{ _scene = scene; }

ScenePtr Engine::getScene() const noexcept
{ return _scene; }

std::pair<int32_t, int32_t> Engine::getWindowSize() noexcept
{ return _mainWindow.getWindowSize(); }

void Engine::run(const Window& window) noexcept
{
    VertexShader vertex(GL_VERTEX_SHADER);
    FragmentShader frag(GL_FRAGMENT_SHADER);

    vertex.addSource(loadShaderFromFile("shaders/primitive/primitive.vert.glsl"));
    frag.addSource(loadShaderFromFile("shaders/primitive/primitive.frag.glsl"));

    ShaderProgram shader;
   
    shader.attachShader(vertex);
    shader.attachShader(frag);

    shader.link();
    
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        if(_eventListener) _eventListener -> onRender();

        glfwPollEvents();

        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        _scene->_object -> render(*_scene->_camera, shader);

        glfwSwapBuffers(window);
    }
}