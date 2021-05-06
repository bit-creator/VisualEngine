#include "engine.h"
#include "GL/FrameBuffer.h"

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
	return window.getWindowSize();
}

std::vector<EventListenerPtr>& Engine::getListeners() noexcept {
	return _eventListeners;
}

void Engine::run(const Window& window) noexcept {
	FrameBuffer fbo;
//	fbo.enableDepthBuffer();
	fbo.useRenderBuffer();

	if (!fbo.readyToWork()) {
		ERROR("FRAMEBUFFER NOT READY")
	}

	fbo.unbind();

    while (!glfwWindowShouldClose(window))
    {
    	fbo.bind();

    	glEnable(GL_DEPTH_TEST);

    	for(EventListenerPtr listener : _eventListeners)
        	if(listener) listener -> onRender();

        auto c = _scene->getBackgroundColor();
        glClearColor(c.x, c.y, c.z, c.w);
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_DEPTH_BUFFER_BIT);

        if (_scene -> useSkyBox()) renderSkyBox();

        for(auto obj : _scene->getDrawList())
        	render(*obj, _scene->getLightList());

        fbo.unbind();

        glDisable(GL_DEPTH_TEST);

        renderScreen(fbo.getColorTextures()[0]);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Engine::renderSkyBox() {
	Draw drawSkyBox;

	drawSkyBox._type = (int)ShaderType::SHADER_SKYBOX;
	drawSkyBox._attribHash =_skyBox.getAttributeHash();

	ShaderProgram& prg = _factory.getShader(drawSkyBox);
	prg.enable();

	glm::mat4 viewMat = glm::inverse(_scene->getCamera()->getWorldMat());
	glm::mat4 projMat = _scene->getCamera()->getProjectionMatrix();

	auto MVPmat = projMat * glm::mat4(glm::mat3(viewMat));

	_scene->getSkyBox()->bind(TextureUnit::SkyBox);

	prg.setUniform("uSkyBoxMVPMat", MVPmat);
	prg.setUniform("uSkyBox", (int)TextureUnit::SkyBox);

	_skyBox.bindBuffers();

	glDrawElements(_skyBox.getPoligonConnectMode(), _skyBox.getNumIndices(), GL_UNSIGNED_INT, 0);

	_skyBox.unbindBuffers();
}

void Engine::renderScreen(TexPtr screenTexture) {
	Draw drawScreen;

	drawScreen._type = (int)ShaderType::SHADER_SCREEN;
	drawScreen._attribHash = _screen.getAttributeHash();

	ShaderProgram& prg = _factory.getShader(drawScreen);
	prg.enable();

	screenTexture->bind(TextureUnit::Screen);
	prg.setUniform("uScreen", (int)TextureUnit::Screen);

	_screen.bindBuffers();

	glDrawArrays(_screen.getPoligonConnectMode(), 0, _screen.getNumVertexes());

	_screen.unbindBuffers();

	screenTexture->unbind();
}

void Engine::render(Object3D &obj, LightList lights) noexcept {
    auto material = obj.getMaterial();
    auto geom = obj.getGeometry();
    auto cam = _scene->getCamera();

    Draw drawData;

    drawData._attribHash = geom->getAttributeHash();
    drawData._hasPerspectiveCamera = (int)cam->getType();
    drawData._numOfLight = lights.size();

    if (geom->hasTexCoord()) {
    	material->setDrawData(drawData);
    	if (_scene->useSkyBox()) drawData._hasSkyBoxMap   = true;
    }

    ShaderProgram& prg = _factory.getShader(drawData);
    prg.enable();

    glm::mat4 modelMat = obj.getWorldMat();
    glm::mat4 viewMat = glm::inverse(cam->getWorldMat());
    glm::mat4 projMat = cam->getProjectionMatrix();

    glm::mat3 nMat = glm::inverse(glm::transpose(modelMat));
    glm::mat4 mVPMat = projMat * viewMat * modelMat;

    if (drawData._hasSkyBoxMap) {
    	_scene->getSkyBox()->bind(TextureUnit::SkyBox);
		prg.setUniform("uSkyBox",      (int)TextureUnit::SkyBox);
    }

    material->setUniforms(prg);

    prg.setUniform("uRoughness", 1 / material->getRoughness());
    prg.setUniform("uCamPos", cam->getPosition());

    prg.setUniform("uMVPMat", mVPMat);
    prg.setUniform("uNormalMat", nMat);
    prg.setUniform("uModelMat", modelMat);

    int ind = 0;

    for(auto light : lights) {
    	auto dirName = getLightsName(ind).append("lightDir");
    	auto colName = getLightsName(ind).append("lightColor");

    	auto dir = glm::mat3(light->getWorldMat()) * glm::normalize(glm::vec3(0., 0., 1.));
    	Color color = light->getColor();

    	prg.setUniform(dirName, dir);
    	prg.setUniform(colName, color.getColorSource());

		++ind;
    }

    glPolygonMode(GL_FRONT_AND_BACK, material->getPolygonsFillMode());

    material->bindMaps();
    geom->bindBuffers();

    if (geom->hasIndexes()) glDrawElements(geom->getPoligonConnectMode(), geom->getNumIndices(), GL_UNSIGNED_INT, 0);
    else glDrawArrays(geom->getPoligonConnectMode() , 0, geom->getNumVertexes());

    geom->unbindBuffers();
    material->unbindMaps();
}
