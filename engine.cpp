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
	return window.getWindowSize();
}

std::vector<EventListenerPtr>& Engine::getListeners() noexcept {
	return _eventListeners;
}

void Engine::run(const Window& window) noexcept {
	glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
    	for(EventListenerPtr listener : _eventListeners)
        	if(listener) listener -> onRender();

        glfwPollEvents();

        auto c = _scene->getBackgroundColor();
        glClearColor(c.x, c.y, c.z, c.w);
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_DEPTH_BUFFER_BIT);

        if (_scene -> useSkyBox()) renderSkyBox();

        for(auto obj : _scene->getDrawList())
        	render(*obj, _scene->getLightList());

        glfwSwapBuffers(window);
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

	_scene->getSkyBox()->bind(0);

	prg.setUniform("uSkyBoxMVPMat", MVPmat);
	prg.setUniform("uSkyBox", 0);

	_skyBox.bindBuffers();

	glDrawElements(_skyBox.getPoligonConnectMode(), _skyBox.getNumIndices(), GL_UNSIGNED_INT, 0);

	_skyBox.unbindBuffers();
}

void Engine::render(Object3D &obj, LightList lights) noexcept {
    enum class TextureUnit {
    	Ambient  =0,
    	Diffuse  =1,
    	Specular =2,
		Rougness =3,
		SkyBox   =4,
		Normal   =5,
		Height   =6
    };

    auto material = obj.getMaterial();
    auto geom = obj.getGeometry();
    auto cam = *_scene->getCamera();

    Draw drawData;

    drawData._type = (int)material->getType();
    drawData._attribHash = geom->getAttributeHash();
    drawData._hasPerspectiveCamera = (int)cam.getType();
    drawData._numOfLight = lights.size();

    if (geom->hasTexCoord()) {
    	if (material->getAmbientTexture() != nullptr)  drawData._hasAmbientMap  = true;
    	if (material->getDiffuseTexture() != nullptr)  drawData._hasDiffuseMap  = true;
    	if (material->getSpecularTexture() != nullptr) drawData._hasSpecularMap = true;
    	if (material->getRougnessTexture() != nullptr) drawData._hasRougnessMap = true;
    	if (material->getNormalTexture() != nullptr)   drawData._hasNormalMap   = true;
    	if (material->getHeightTexture() != nullptr)   drawData._hasHeightMap   = true;
    	if (_scene->useSkyBox())					   drawData._hasSkyBoxMap   = true;
    }

    ShaderProgram& prg = _factory.getShader(drawData);
    prg.enable();

    glm::mat4 modelMat = obj.getWorldMat();
    glm::mat4 viewMat = glm::inverse(cam.getWorldMat());
    glm::mat4 projMat = cam.getProjectionMatrix();
    glm::mat3 nMat = glm::inverse(glm::transpose(modelMat));

    if (drawData._hasAmbientMap)  material->getAmbientTexture() ->bind((int)TextureUnit::Ambient);
    if (drawData._hasDiffuseMap)  material->getDiffuseTexture() ->bind((int)TextureUnit::Diffuse);
    if (drawData._hasSpecularMap) material->getSpecularTexture()->bind((int)TextureUnit::Specular);
    if (drawData._hasRougnessMap) material->getRougnessTexture()->bind((int)TextureUnit::Rougness);
    if (drawData._hasNormalMap)   material->getNormalTexture()  ->bind((int)TextureUnit::Normal);
    if (drawData._hasHeightMap)   material->getHeightTexture()  ->bind((int)TextureUnit::Height);
    if (drawData._hasSkyBoxMap)   _scene->getSkyBox()->bind((int)TextureUnit::SkyBox);

    prg.setUniform("uTexAmbient",  (int)TextureUnit::Ambient);
    prg.setUniform("uTexDiffuse",  (int)TextureUnit::Diffuse);
    prg.setUniform("uTexSpecular", (int)TextureUnit::Specular);
    prg.setUniform("uTexRougness", (int)TextureUnit::Rougness);
    prg.setUniform("uTexNormal",   (int)TextureUnit::Normal);
    prg.setUniform("uTexHeight",   (int)TextureUnit::Height);
    prg.setUniform("uSkyBox",      (int)TextureUnit::SkyBox);

    if(material->getType() == MaterialType::MATERIAL_BUMP)
    {
    	auto bumpMaterial = (BumpMaterial*)material.get();
    	prg.setUniform("uScale", bumpMaterial->_scale);
    }

    auto mVPMat = projMat * viewMat * modelMat;
    auto modelViewMat = viewMat * modelMat;

    prg.setUniform("uGlossyColor", material->getAmbientColor().getColorSource());
    prg.setUniform("uAmbientColor", material->getAmbientColor().getColorSource());
    prg.setUniform("uDiffuseColor", material->getDiffuseColor().getColorSource());
    prg.setUniform("uSpecularColor", material->getSpecularColor().getColorSource());

    prg.setUniform("uRoughness", 1 / material->getRoughness());

    prg.setUniform("uCamPos", cam.getPosition());

    prg.setUniform("uFirstRefractiveIndex", 1.33f);
    prg.setUniform("uSecondRefractiveIndex", 1.52f);

    prg.setUniform("uMVPMat", mVPMat);
    prg.setUniform("uNormalMat", nMat);
    prg.setUniform("uModelViewMat", modelViewMat);
    prg.setUniform("uModelMat", modelMat);
    prg.setUniform("uCameraPos", cam.getPosition());

    int ind = 0;

    for(auto light : lights)
    {
    	auto dirName = getLightsName(ind).append("lightDir");
    	auto colName = getLightsName(ind).append("lightColor");

    	auto dir = glm::mat3(light->getWorldMat()) * glm::normalize(glm::vec3(0., 0., 1.));
    	Color color = light->getColor();

    	prg.setUniform(dirName, dir);
    	prg.setUniform(colName, color.getColorSource());

		++ind;
    }

    glPolygonMode(GL_FRONT_AND_BACK, material->getPolygonsFillMode());

    geom->bindBuffers();

    if (geom->hasIndexes()) glDrawElements(geom->getPoligonConnectMode(), geom->getNumIndices(), GL_UNSIGNED_INT, 0);
    else glDrawArrays(geom->getPoligonConnectMode() , 0, geom->getNumVertexes());

    geom->unbindBuffers();


    if (geom->hasTexCoord())
    {
    	if (material->getAmbientTexture() != nullptr)
    	{
    		material->getAmbientTexture()->unbind();
    	}

    	if (material->getDiffuseTexture() != nullptr)
    	{
    		material->getDiffuseTexture()->unbind();
    	}

    	if (material->getSpecularTexture() != nullptr)
    	{
    		material->getSpecularTexture()->unbind();
    	}
    }
}
