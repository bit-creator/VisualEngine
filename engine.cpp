#include "engine.h"
#include "GL/FrameBuffer.h"
#include <chrono>

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
    	auto frame_begin = std::chrono::high_resolution_clock::now();

    	for(EventListenerPtr listener : _eventListeners)
        	if(listener) listener -> onRender();

        for(Object3D& obj : _scene->objects) {
        	if((!obj.isDied()) && obj.isEnabled())
        		obj.update();
        }

        for(Node& obj : _scene->nodes) {
        	if(!obj.isDied() && obj.isEnabled())
        		obj.update();
        }

        for(Light& obj : _scene->lights) {
        	if(!obj.isDied() && obj.isEnabled())
        		obj.update();
        }

        _scene->getCamera()->update();

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

        for(Object3D& obj : _scene->objects) {
//        	if(!obj.isDied())
        	if(!obj.isDied() && obj.isEnabled())
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

        auto frame_end = std::chrono::high_resolution_clock::now();

//        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(frame_end - frame_begin).count() << std::endl;
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
	auto lightDirName = [] (int ind)->std::string {
		std::string patern = "Lights[%].direction";
		std::replace(patern.begin(), patern.end(), '%', (char)(ind + '0'));
		return patern;
	};

	auto lightColName = [] (int ind)->std::string {
		std::string patern = "Lights[%].color";
		std::replace(patern.begin(), patern.end(), '%', (char)(ind + '0'));
		return patern;
	};

	Draw drawScreen;

	if (_scene -> useSkyBox()) drawScreen._hasSkyBoxMap = true;
	drawScreen._shaderType = (int)ShaderType::SHADER_SCREEN;
	drawScreen._materialType = (int)ShaderType::SHADER_SCREEN;
	drawScreen._renderTargets = _FBO.TargetHash();
	drawScreen._attribHash = _screen.getAttributeHash();
	drawScreen._numOfDirLight = _scene->lights.getDirectionLightCapacity();
	drawScreen._numOfPointLight = _scene->lights.getPointLightCapacity();
	drawScreen._numOfSpotLight = _scene->lights.getSpotLightCapacity();

	ShaderProgram& prg = _factory.getShader(drawScreen);
	prg.enable();

	prg.setUniform("uAlbedoMap", (int)RenderingTarget::ALBEDO);
	prg.setUniform("uNormalMap", (int)RenderingTarget::NORMAL);
	prg.setUniform("uViewMap", (int)RenderingTarget::VIEW);

    if (_scene -> useSkyBox()) {
    	_scene->getSkyBox()->bind(TextureUnit::SkyBox);
		prg.setUniform("uSkyBox", (int)TextureUnit::SkyBox);
    }

    int direct = -1;
    int point = -1;
    int spot = -1;

    for(Light& light : _scene->lights) {
    	std::string dirName = "";
    	std::string colName = "";

    	switch (light.getType()) {
    	case LightType::DIRECTIONAL: {
    		dirName = "uDir" + lightDirName(++direct);
			colName = "uDir" + lightColName(direct);
			break;
    	}
    	case LightType::POINT: {
    		dirName = "uPoint" + lightDirName(++point);
			colName = "uPoint" + lightColName(point);
			break;
    	}
    	case LightType::SPOT: {
    		dirName = "uSpot" + lightDirName(++spot);
			colName = "uSpot" + lightColName(spot);
			break;
    	}
    	}

    	auto dir = glm::mat3(light.getWorldMat()) * glm::normalize(glm::vec3(0., 0., 1.));
//    	auto dir = glm::mat3(light.getWorldMat()) * glm::normalize(glm::vec3(0., 0., 1.));
    	Color color = light.getColor();

    	prg.setUniform(dirName, dir);
    	prg.setUniform(colName, color.getColorSource());


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

    prg.setUniform("uCamPos", cam->transform.getPosition());

    prg.setUniform("uMVPMat", mVPMat);
    prg.setUniform("uNormalMat", nMat);
    prg.setUniform("uModelMat", modelMat);

    prg.setUniform("uObjectColorKey", obj.getColorKey());

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

Entity* Engine::getPool(EntityType type) {
	return Engine::engine().getScene()->getPool(type);
}

ScenePtr Engine::scene() {
	return engine().getScene();
}
