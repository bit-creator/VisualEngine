#include "scene.h"
#include "constants.hpp"

Scene::Scene() noexcept
	: _background(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
	, _camera(PerspectiveCamera(PI / 3, 1, 0.1, 100))
	, _root(Node::reference(0, NodeType::NODE_NODE))
	, objects(30)
	, lights(30)
	, nodes(30)
{
//	auto nod = nodes.capture();
//	_root = nodes[0];
}

void Scene::setCamera(Camera camera) noexcept {
//	_root->addChild(camera);
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

Node::reference Scene::getRoot() noexcept {
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

Node* Scene::getPool(NodeType type) {
	switch(type) {
	case NodeType::NODE_CAMERA: return getCamera();
	case NodeType::NODE_OBJECT: return objects.undegroundArray();
	case NodeType::NODE_LIGHT:  return lights.undegroundArray();
	case NodeType::NODE_NODE:   return nodes.undegroundArray();
	}; return nullptr;
}

Node::reference Scene::findObject(size_t ID) {
	for(size_t ind = 0; ind < objects.size(); ++ind) {
		if (ID == objects[ind].getID()) return Node::reference(ind, NodeType::NODE_OBJECT);
	} return Node::reference();
}
