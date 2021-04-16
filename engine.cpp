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
	ShaderProgram* prg = &_factory.getShader(ShaderType::SHADER_SKYBOX);
	prg->enable();

	glm::mat4 viewMat = glm::inverse(_scene->getCamera()->getWorldMat());
	glm::mat4 projMat = _scene->getCamera()->getProjectionMatrix();

	auto MVPmat = projMat * glm::mat4(glm::mat3(viewMat));

	_scene->getSkyBox()->bind(0);

	prg->setUniform("uSkyBoxMVPMat", MVPmat);
	prg->setUniform("uSkyBox", 0);

	_skyBox.bindBuffers();

	glDrawElements(_skyBox.getPoligonConnectMode(), _skyBox.getNumIndices(), GL_UNSIGNED_INT, 0);

	_skyBox.unbindBuffers();
}

void Engine::render(Object3D &obj, LightList lights) noexcept {
    auto material = obj.getMaterial();
    auto geom = obj.getGeometry();

    ShaderProgram* prog;
    auto cam = *_scene->getCamera();

    switch(material->getType()) {
    case MaterialType::MATERIAL_BUMP:
    	prog = &_factory.getShader(ShaderType::SHADER_BUMP);
    	break;

    case MaterialType::MATERIAL_PHONG:
    	prog = &_factory.getShader(ShaderType::SHADER_PHONG);
    	break;

    case MaterialType::MATERIAL_GLOSSY:
    	prog = &_factory.getShader(ShaderType::SHADER_GLOSSY);
    	break;

    case MaterialType::MATERIAL_GLASS:
    	prog = &_factory.getShader(ShaderType::SHADER_GLASS);
    	break;
    }

    prog->enable();

    glm::mat4 modelMat = obj.getWorldMat();
    glm::mat4 viewMat = glm::inverse(cam.getWorldMat());
    glm::mat4 projMat = cam.getProjectionMatrix();
    glm::mat3 nMat = glm::inverse(glm::transpose(modelMat));

    enum class TextureUnit {
    	Ambient =0,
    	Diffuse =1,
    	Specular =2,
		SkyBox =4,
		Normal = 5,
		Height = 6
    };

    if (_scene->useSkyBox()) {
    	prog->setUniform("uHasSkyBox", true);
    	_scene->getSkyBox()->bind((int)TextureUnit::SkyBox);
    	prog->setUniform("uSkyBox", (int)TextureUnit::SkyBox);
    }

    if (geom->hasTexCoord())
    {
    	if (material->getHeightTexture() != nullptr)
    	{
    		material->getHeightTexture()->bind((int)TextureUnit::Height);
    	    prog->setUniform("uHasHeightMap", true);
    	    prog->setUniform("uTexHeight", (int)TextureUnit::Height);
    	}
    	else prog->setUniform("uHasHeightMap", false);


    	if (material->getNormalTexture() != nullptr)
    	{
    	    material->getNormalTexture()->bind((int)TextureUnit::Normal);
    	    prog->setUniform("uHasNormalMap", true);
    		prog->setUniform("uTexNormal", (int)TextureUnit::Normal);
    	}
    	else prog->setUniform("uHasNormalMap", false);


    	if (material->getAmbientTexture() != nullptr)
    	{
    		material->getAmbientTexture()->bind((int)TextureUnit::Ambient);
    		prog->setUniform("uHasAmbientMap", true);
    		prog->setUniform("uTexAmbient", (int)TextureUnit::Ambient);
    	}
		else prog->setUniform("uHasAmbientMap", false);

    	if (material->getDiffuseTexture() != nullptr)
    	{
    		material->getDiffuseTexture()->bind((int)TextureUnit::Diffuse);
    		prog->setUniform("uHasDiffuseMap", true);
    		prog->setUniform("uTexDiffuse", (int)TextureUnit::Diffuse);
    	}
		else prog->setUniform("uHasDiffuseMap", false);

    	if (material->getSpecularTexture() != nullptr)
    	{
    		material->getSpecularTexture()->bind((int)TextureUnit::Specular);
    		prog->setUniform("uHasSpecularMap", true);
    		prog->setUniform("uTexSpecular", (int)TextureUnit::Specular);
    	}
    	else prog->setUniform("uHasSpecularMap", false);
    }
    else
    {
    	prog->setUniform("uHasAmbientMap", false);
    	prog->setUniform("uHasDiffuseMap", false);
    	prog->setUniform("uHasSpecularMap", false);
    	prog->setUniform("uHasAmbientMap", false);
    	prog->setUniform("uHasHeightMap", false);
    }

    if(material->getType() == MaterialType::MATERIAL_BUMP)
    {
    	auto bumpMaterial = (BumpMaterial*)material.get();
    	prog->setUniform("uScale", bumpMaterial->_scale);
    }

    auto mVPMat = projMat * viewMat * modelMat;
    auto modelViewMat = viewMat * modelMat;

    prog->setUniform("uAmbientColor", material->getAmbientColor().getColorSource());
    prog->setUniform("uDiffuseColor", material->getDiffuseColor().getColorSource());
    prog->setUniform("uSpecularColor", material->getSpecularColor().getColorSource());
    prog->setUniform("uRoughness", 1 / material->getRoughness());
    prog->setUniform("uPerspectiveCamera", (int)cam.getType());
    prog->setUniform("uCamPos", cam.getPosition());
    prog->setUniform("uFirstRefractiveIndex", 1.33f);
    prog->setUniform("uSecondRefractiveIndex", 1.52f);

    prog->setUniform("uMVPMat", mVPMat);
    prog->setUniform("uNormalMat", nMat);
    prog->setUniform("uModelViewMat", modelViewMat);
    prog->setUniform("uModelMat", modelMat);
    prog->setUniform("uCameraPos", cam.getPosition());
    prog->setUniform("uLightCount", (int)lights.size());

    int ind = 0;

    for(auto light : lights)
    {
    	auto dirName = getLightsName(ind).append("lightDir");
    	auto colName = getLightsName(ind).append("lightColor");

    	auto dir = glm::mat3(light->getWorldMat()) * glm::normalize(glm::vec3(0., 0., 1.));
    	Color color = light->getColor();

    	prog->setUniform(dirName, dir);
    	prog->setUniform(colName, color.getColorSource());

		++ind;
    }

    glPolygonMode(GL_FRONT_AND_BACK, material->getPolygonsFillMode());

    geom->bindBuffers();

//    glEnableVertexAttribArray(0); CHECK_GL_ERROR();
//    glEnableVertexAttribArray(1); CHECK_GL_ERROR();
//    glEnableVertexAttribArray(2); CHECK_GL_ERROR();
//    glEnableVertexAttribArray(3); CHECK_GL_ERROR();
//    glEnableVertexAttribArray(4); CHECK_GL_ERROR();
//    glEnableVertexAttribArray(5); CHECK_GL_ERROR();

    if (geom->hasIndexes()) glDrawElements(geom->getPoligonConnectMode(), geom->getNumIndices(), GL_UNSIGNED_INT, 0);
    else glDrawArrays(geom->getPoligonConnectMode() , 0, geom->getNumVertexes());

//    glDisableVertexAttribArray(0); CHECK_GL_ERROR();
//    glDisableVertexAttribArray(1); CHECK_GL_ERROR();
//    glDisableVertexAttribArray(2); CHECK_GL_ERROR();
//    glDisableVertexAttribArray(3); CHECK_GL_ERROR();
//    glDisableVertexAttribArray(4); CHECK_GL_ERROR();
//    glDisableVertexAttribArray(5); CHECK_GL_ERROR();

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
