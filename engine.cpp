#include "engine.h"

Engine& Engine::engine() noexcept {
	static Engine engine; return engine;
}

void Engine::addEventListener(EventListenerPtr eventListener) {
    _eventListeners.push_back(eventListener);
}

void Engine::setScene(ScenePtr scene) noexcept {
	_scene = scene;
}

ScenePtr Engine::getScene() const noexcept {
	return _scene;
}

std::pair<int32_t, int32_t> Engine::getWindowSize() noexcept {
	return _mainWindow.getWindowSize();
}

std::vector<EventListenerPtr>& Engine::getListeners() noexcept {
	return _eventListeners;
}

void Engine::run(const Window& window) noexcept {
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
    	for(EventListenerPtr listener : _eventListeners)
        	if(listener) listener -> onRender();

        glfwPollEvents();

        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        render(*_scene->_object, *_scene->_camera, shader);

        glfwSwapBuffers(window);
    }
}

void Engine::render(const Object3D &obj, const Camera &cam,
		ShaderProgram &prg) noexcept {
	prg.enable();

    auto material = obj.getMaterial();
    auto geom = obj.getGeometry();

    glm::mat4 modelMat = ((Node)obj).getModelMat();
    glm::mat4 viewMat = glm::inverse(((Node)cam).getModelMat());
    glm::mat4 projMat = cam.getProjectionMatrix();
    glm::mat3 nMat = glm::inverse(glm::transpose(modelMat));

    auto mVPMat = projMat * viewMat * modelMat;
    auto modelViewMat = viewMat * modelMat;

    prg.setUniform("uAmbientColor", material->getColor(ColorTarget::Ambient));
    prg.setUniform("uDiffuseColor", material->getColor(ColorTarget::Diffuse));
    prg.setUniform("uSpecularColor", material->getColor(ColorTarget::Specular));
    prg.setUniform("uRoughness", 1 / material->getRoughness());
    prg.setUniform("uPerspectiveCamera", (int)cam.getType());

    prg.setUniform("uMVPMat", mVPMat);
    prg.setUniform("uNormalMat", nMat);
    prg.setUniform("uModelViewMat", modelViewMat);
    prg.setUniform("uLightDir", glm::normalize(glm::vec3(0., 0., 1.)));

    glPolygonMode(GL_FRONT_AND_BACK, material->getPolygonsFillMode());

    geom->bindBuffers();

    if (geom->hasIndexes()) glDrawElements(geom->getPoligonConnectMode(), geom->getNumIndices(), GL_UNSIGNED_INT, 0);
    else glDrawArrays(geom->getPoligonConnectMode() , 0, geom->getNumVertexes());

    geom->unbindBuffers();
}
