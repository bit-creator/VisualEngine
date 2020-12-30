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

        auto c = _scene->getBackgroundColor();
        glClearColor(c.x, c.y, c.z, c.w);
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_DEPTH_BUFFER_BIT);

        for(auto obj : _scene->getDrawList())
        	render(*obj, *_scene->getCamera(), _scene->getLightList(), shader);

        glfwSwapBuffers(window);
    }
}

void Engine::render(Object3D &obj, Camera &cam, LightList lights,
		ShaderProgram &prg) noexcept {
	prg.enable();

    auto material = obj.getMaterial();
    auto geom = obj.getGeometry();

    glm::mat4 modelMat = obj.getWorldMat();
    glm::mat4 viewMat = glm::inverse(cam.getWorldMat());
    glm::mat4 projMat = cam.getProjectionMatrix();
    glm::mat3 nMat = glm::inverse(glm::transpose(modelMat));

    enum class TextureUnit {
    	Ambient =0,
    	Diffuse =1,
    	Specular =2,
    };

    if (geom->hasTexCoord())
    {
    	if (material->getAmbientTexture() != nullptr)
    	{
    		material->getAmbientTexture()->bind((int)TextureUnit::Ambient);
			prg.setUniform("uHasAmbientMap", true);
			prg.setUniform("uTexAmbient", (int)TextureUnit::Ambient);
    	}
		else prg.setUniform("uHasAmbientMap", false);

    	if (material->getDiffuseTexture() != nullptr)
    	{
    		material->getDiffuseTexture()->bind((int)TextureUnit::Diffuse);
			prg.setUniform("uHasDiffuseMap", true);
			prg.setUniform("uTexDiffuse", (int)TextureUnit::Diffuse);
    	}
		else prg.setUniform("uHasDiffuseMap", false);

    	if (material->getSpecularTexture() != nullptr)
    	{
    		material->getSpecularTexture()->bind((int)TextureUnit::Specular);
    		prg.setUniform("uHasSpecularMap", true);
    		prg.setUniform("uTexSpecular", (int)TextureUnit::Specular);
    	}
    	else prg.setUniform("uHasSpecularMap", false);
    }
    else
    {
    	prg.setUniform("uHasAmbientMap", false);
    	prg.setUniform("uHasDiffuseMap", false);
    	prg.setUniform("uHasSpecularMap", false);
    }

    auto mVPMat = projMat * viewMat * modelMat;
    auto modelViewMat = viewMat * modelMat;

    prg.setUniform("uAmbientColor", material->getAmbientColor().getColorSource());
    prg.setUniform("uDiffuseColor", material->getDiffuseColor().getColorSource());
    prg.setUniform("uSpecularColor", material->getSpecularColor().getColorSource());
    prg.setUniform("uRoughness", 1 / material->getRoughness());
    prg.setUniform("uPerspectiveCamera", (int)cam.getType());

    prg.setUniform("uMVPMat", mVPMat);
    prg.setUniform("uNormalMat", nMat);
    prg.setUniform("uModelViewMat", modelViewMat);
    prg.setUniform("uLightCount", (int)lights.size());

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
}
