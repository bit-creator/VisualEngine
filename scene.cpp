#include "scene.h"
#include "constants.hpp"

Scene::Scene() noexcept
	: _background(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
	, _camera(PerspectiveCamera(PI / 3, 1, 0.1, 100))
	, _root(Entity::reference(0, EntityType::NODE))
	, objects(30)
	, lights(30)
	, nodes(30)
{
//	auto nod = nodes.capture();
//	_root = nodes[0];
}

void Scene::setCamera(Camera camera) noexcept {
	_root->addChild(Entity::reference(0, EntityType::CAMERA));
	_camera = camera;
}

Camera* Scene::getCamera() noexcept {
	return &_camera;
}

void Scene::setBackgroundColor(const glm::vec4 &color) noexcept {
	_background = color;
}

const glm::vec4& Scene::getBackgroundColor() const noexcept {
	return _background;
}

Entity::reference Scene::root() noexcept {
	return _root;
}

void Scene::disableSkyBox() {
	_skyBox = nullptr;
}

bool Scene::useSkyBox() const {
	return _skyBox != nullptr;
}

void Scene::loadSkyboxImage(BoxSide side, TexPtr skyBox, std::string filename) {
}

void Scene::setSkyBox(TexPtr skyBox) {
	_skyBox = skyBox;
}

TexPtr Scene::getSkyBox() const {
	return _skyBox;
}

Entity* Scene::getPool(EntityType type) {
	switch(type) {
	case EntityType::CAMERA: return getCamera();
	case EntityType::OBJECT: return objects.undegroundArray();
	case EntityType::LIGHT:  return lights.undegroundArray();
	case EntityType::NODE:   return nodes.undegroundArray();
	}; return nullptr;
}

Entity::reference Scene::findObject(size_t ID) {
	for(size_t ind = 0; ind < objects.maxSize(); ++ind) {
		if(!objects[ind].isDied()) {
			if (ID == objects[ind].getID()) {
				return Entity::reference(ind, EntityType::OBJECT);
			}
		}
	} return Entity::reference();
}
