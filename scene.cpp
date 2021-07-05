#include "scene.h"
#include "constants.hpp"

Scene::Scene() noexcept
	: _background(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
//	, _camera(std::make_shared<Camera>(PerspectiveCamera(PI / 3, 1, 0.1, 100)))
	, _camera(PerspectiveCamera(PI / 3, 1, 0.1, 100))
//	, _root(std::make_shared<Node>(NodeType::NODE_NODE))

	, _root(Node::reference())
{
	auto nod = Node::reference(nodes.allocate(), NodeType::NODE_NODE);
	_root = nod;
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

Node::reference Scene::getRoot() const noexcept {
	return _root;
}

//DrawList Scene::getDrawList() const noexcept {
//	DrawList result;
//	getDrawListImpl(result, _root);
//	return result;
//}

//void Scene::getDrawListImpl(DrawList &list, const NodePtr& obj) const noexcept {
//	for(auto child : obj->getChilds()) {
//		if(child->isEnabled()) {
//			getDrawListImpl(list, child);
//			if(child->getNodeType() == NodeType::NODE_OBJECT)
//				list.push_back((Object3D*)child.get());
//		}
//	}
//}

void Scene::disableSkyBox() {
	_skyBox = nullptr;
}

bool Scene::useSkyBox() const {
	return _skyBox != nullptr;
}

void Scene::loadSkyboxImage(BoxSide side, TexPtr skyBox, std::string filename) {
}

//LightList Scene::getLightList() const noexcept {
//	LightList result;
//	getLightListImpl(result, _root);
//	return result;
//}

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

Node::reference Scene::searchID(size_t ID) {
	for(size_t ind = 0; ind < objects.size(); ++ind) {
		if (ID == objects[ind].getID()) return Node::reference(ind, NodeType::NODE_OBJECT);
	} return Node::reference();
}
//void Scene::getLightListImpl(LightList &list, const NodePtr &obj) const noexcept {
//	for(auto child : obj->getChilds()) {
//		getLightListImpl(list, child);
//	if(child->getNodeType() == NodeType::NODE_LIGHT)
//		list.push_back((Light*)child.get());
//	}
//}
