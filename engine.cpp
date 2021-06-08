#include "engine.h"
#include "GL/FrameBuffer.h"

Engine::Engine() noexcept {
	_FBO.bind();

	_FBO.attachNewColorTex(RenderingTarget::PICKER, Object3D::getColorKeyFormat());
	_FBO.attachNewColorTex(RenderingTarget::VIEW);
	_FBO.attachNewColorTex(RenderingTarget::NORMAL);
	_FBO.attachNewColorTex(RenderingTarget::SCREEN);
	_FBO.attachNewColorTex(RenderingTarget::ALBEDO);
//	_FBO.enableDepthBuffer();
//	_FBO.enableStencilBuffer();
//	_FBO.enableDepthStencilBuffer();


	_FBO.useRenderBuffer();
}

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
	if (!_FBO.readyToWork()) {
		ERROR("FRAMEBUFFER NOT READY")
	}

	if (!_SBO.readyToWork()) {
		ERROR("FRAMEBUFFER NOT READY")
	}

    while (!glfwWindowShouldClose(window))
    {
    	for(EventListenerPtr listener : _eventListeners)
        	if(listener) listener -> onRender();

    	_FBO.bind();
        _FBO.bindTextures();

    	glEnable(GL_DEPTH_TEST);

        auto c = _scene->getBackgroundColor();
        glClearColor(c.x, c.y, c.z, c.w);
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_DEPTH_BUFFER_BIT);

        if (_scene -> useSkyBox()) renderSkyBox();

    	glEnable(GL_STENCIL_TEST);
    	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    	glClear(GL_STENCIL_BUFFER_BIT);

    	glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        float index = 0.0;
        for(auto& obj : objects) {
        	if(obj.isEnabled())
        		geometryPass(obj);
        }


        glDisable(GL_DEPTH_TEST);

        _FBO.bindTextures();

        	glStencilFunc(GL_EQUAL, 1, 0xFF);
        	glStencilMask(0x00);

//        	lightPass(_scene->getLightList());
        	lightPass();


        	glStencilMask(0xFF);
        	glDisable(GL_STENCIL_TEST);

        _FBO.unbindTextures();

        _FBO.unbind();

        _FBO.bindTextures();
        	renderScreen();
        _FBO.unbindTextures();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Engine::renderSkyBox() {
    auto cam = _scene->getCamera();

	Draw drawSkyBox;

	drawSkyBox._shaderType = (int)ShaderType::SHADER_SKYBOX;
	drawSkyBox._materialType = (int)ShaderType::SHADER_SKYBOX;
	drawSkyBox._attribHash =_skyBox.getAttributeHash();
	drawSkyBox._renderTargets = _FBO.TargetHash();

	ShaderProgram& prg = _factory.getShader(drawSkyBox);
	prg.enable();

	glm::mat4 viewMat = glm::inverse(_scene->getCamera()->getWorldMat());
	glm::mat4 projMat = cam->getProjectionMatrix();

	auto MVPmat = projMat * glm::mat4(glm::mat3(viewMat));

	_scene->getSkyBox()->bind(TextureUnit::SkyBox);

	prg.setUniform("uSkyBoxMVPMat", MVPmat);
	prg.setUniform("uSkyBox", (int)TextureUnit::SkyBox);

	_skyBox.bindBuffers();

	glDrawElements(_skyBox.getPoligonConnectMode(), _skyBox.getNumIndices(), GL_UNSIGNED_INT, 0);

	_skyBox.unbindBuffers();
}

void Engine::renderScreen() {
	Draw drawScreen;

	drawScreen._shaderType = (int)ShaderType::SHADER_TEXTURE_RENDER;
	drawScreen._materialType = (int)ShaderType::SHADER_TEXTURE_RENDER;
	drawScreen._renderTargets = _FBO.TargetHash();
	drawScreen._attribHash = _screen.getAttributeHash();

	ShaderProgram& prg = _factory.getShader(drawScreen);
	prg.enable();

	prg.setUniform("uScreen", (int)RenderingTarget::SCREEN);
	prg.setUniform("uKernel", _postProcesingKernel);
	prg.setUniform("uOffset", 1.0f / 400);

	_screen.bindBuffers();

	glDrawArrays(_screen.getPoligonConnectMode(), 0, _screen.getNumVertexes());

	_screen.unbindBuffers();
}

void Engine::lightPass() {
	Draw drawScreen;

	if (_scene -> useSkyBox()) drawScreen._hasSkyBoxMap = true;
	drawScreen._shaderType = (int)ShaderType::SHADER_SCREEN;
	drawScreen._materialType = (int)ShaderType::SHADER_SCREEN;
	drawScreen._renderTargets = _FBO.TargetHash();
	drawScreen._attribHash = _screen.getAttributeHash();
	drawScreen._numOfLight = lights.size();

	ShaderProgram& prg = _factory.getShader(drawScreen);
	prg.enable();

	prg.setUniform("uAlbedoMap", (int)RenderingTarget::ALBEDO);
	prg.setUniform("uNormalMap", (int)RenderingTarget::NORMAL);
	prg.setUniform("uViewMap", (int)RenderingTarget::VIEW);

    if (_scene -> useSkyBox()) {
    	_scene->getSkyBox()->bind(TextureUnit::SkyBox);
		prg.setUniform("uSkyBox",      (int)TextureUnit::SkyBox);
    }

    int ind = 0;
    for(auto light : lights) {
    	auto dirName = getLightsName(ind).append("lightDir");
    	auto colName = getLightsName(ind).append("lightColor");

    	auto dir = glm::mat3(light.getWorldMat()) * glm::normalize(glm::vec3(0., 0., 1.));
    	Color color = light.getColor();

    	prg.setUniform(dirName, dir);
    	prg.setUniform(colName, color.getColorSource());

		++ind;
    }

	_screen.bindBuffers();

	glDrawArrays(_screen.getPoligonConnectMode(), 0, _screen.getNumVertexes());

	_screen.unbindBuffers();
}

void Engine::geometryPass(Object3D &obj) noexcept {
    auto material = obj.getMaterial();
    auto geom = obj.getGeometry();
    auto cam = _scene->getCamera();

    Draw drawData;

    drawData._attribHash = geom->getAttributeHash();
    drawData._renderTargets = _FBO.TargetHash();
    drawData._hasPerspectiveCamera = (int)cam->getType();

    if (geom->hasTexCoord()) {
    	material->setDrawData(drawData);
    	if (_scene->useSkyBox()) drawData._hasSkyBoxMap   = true;
    }

    drawData._shaderType = (int)ShaderType::SHADER_GEOMETRY_PASS;

    ShaderProgram& prg = _factory.getShader(drawData);
    prg.enable();

    _FBO.bindTextures();

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

    prg.setUniform("uCamPos", cam->getPosition());

    prg.setUniform("uMVPMat", mVPMat);
    prg.setUniform("uNormalMat", nMat);
    prg.setUniform("uModelMat", modelMat);

    prg.setUniform("uObjectColorKey", obj.getColorKey());

    int ind = 0;

    glPolygonMode(GL_FRONT_AND_BACK, material->getPolygonsFillMode());

    material->bindMaps();
    geom->bindBuffers();

    if (geom->hasIndexes()) glDrawElements(geom->getPoligonConnectMode(), geom->getNumIndices(), GL_UNSIGNED_INT, 0);
    else glDrawArrays(geom->getPoligonConnectMode() , 0, geom->getNumVertexes());

    geom->unbindBuffers();
    material->unbindMaps();
}

const glm::mat3& Engine::getPostProcesingKernel() const {
	return _postProcesingKernel;
}

void Engine::setPostProcesingKernel(const glm::mat3 &postProcesingKernel) {
	_postProcesingKernel = postProcesingKernel;
}

float Engine::getPickerKey(const glm::vec2& mousePosition) {
	return _FBO.getPickerKey(mousePosition);
}
