#include "node.h"
#include "object3d.h"
#include "engine.h"

#include <glm/gtc/type_ptr.hpp>

////////// Node::reference ///////////

Node::reference::reference()
	: reference(npos, NodeType::NODE_NODE)
{  }

Node::reference::reference(size_t offset, NodeType type)
	: _offset(offset), _type(type)
{  }

bool Node::reference::expired() const {
	return _offset == npos;
}

void Node::reference::kill() {
	_offset = npos;
}

Node* Node::reference::operator ->() {
	switch(_type) {
	case NodeType::NODE_CAMERA: return Engine::engine().getScene()->getCamera();
	case NodeType::NODE_OBJECT: return ((dynamic_cast<Object3D*>(Engine::getPool(_type))) + _offset);
	case NodeType::NODE_LIGHT:  return ((dynamic_cast<Light*>(Engine::getPool(_type))) + _offset);
	case NodeType::NODE_NODE:   return ((dynamic_cast<Node*>(Engine::getPool(_type))) + _offset);
	} return nullptr;
}

/////////////// NODE //////////////

// creation
Node::Node() noexcept
: Node(NodeType::NODE_NODE) {
}

Node::Node(NodeType type) noexcept
    : _modelMat ( glm::mat4(1.0f) )
    , _rotate   ( glm::quat() )
    , _position ( glm::vec3(0.0f, 0.0f, 0.0f) )
    , _scale    ( glm::vec3(1.0f, 1.0f, 1.0f) )
    , _dirtyTransform(true)
	, _dirtyWorldTransform(true)
	, _enabled(true)
    , _type(type)
{
	_this.kill();
	_next.kill();
}

void Node::initialize() {

}


Node::reference Node::create() {
	return Engine::engine().getScene()->nodes.capture();
}

// copy
Node::Node(const Node &oth) noexcept
	: _parent()
	, _modelMat(oth._modelMat)
	, _worldMat(oth._worldMat)
	, _rotate(oth._rotate)
	, _position(oth._position)
	, _scale(oth._scale)
	, _dirtyTransform(oth._dirtyTransform)
	, _dirtyWorldTransform(true)
	, _enabled(oth._enabled)
	, _type(oth._type)
{  }


Node& Node::operator =(const Node& oth) noexcept{

}


Node::reference Node::copy() {
	auto pool = Engine::engine().getScene()->getPool<Node>();
}

// destruction
Node::~Node() {
}

void Node::deinitialize() {

}

// tree
void Node::addChild(Node::reference child) {
	if(!child->_parent.expired()){
		child ->_parent->removeChild(child);
	}
	_childs.push_back(child);
	child->_parent = _this;

	child->_dirtyWorldTransform = true;
	child->_dirtyTransform = true;
}

void Node::removeChild(Node::reference child) {
	if(_childs.empty()) return;
	_childs.remove(child);
}

std::list < Node::reference >& Node::getChilds() {
	return _childs;
}

void Node::unvalidateWorldMat() noexcept {
	for (auto & node : _childs)
		node->unvalidateWorldMat();

	if (!_dirtyWorldTransform)
	_dirtyWorldTransform = true;
}

// transformation
void Node::setRotate(const glm::vec3& axis, const float angle) noexcept {
	_rotate = glm::angleAxis(angle, glm::normalize(axis));
	_dirtyTransform = true;
	unvalidateWorldMat();
}

void Node::setRotate(const glm::vec3& angels) noexcept {
	_rotate = glm::quat(angels);
	_dirtyTransform = true;
	unvalidateWorldMat();
}

glm::quat Node::getRotate() const noexcept {
	return _rotate;
}

void Node::setScale(const glm::vec3& scale) noexcept {
	_scale = scale;
	_dirtyTransform = true;
	unvalidateWorldMat();
}

glm::vec3 Node::getScale() const noexcept {
	return _scale;
}

void Node::setPosition(const glm::vec3& position) noexcept {
	_position = position;
	_dirtyTransform = true;
	unvalidateWorldMat();
}

glm::vec3 Node::getPosition() const noexcept {
	return _position;
}

glm::mat4 Node::getModelMat() noexcept {
    if(!_dirtyTransform) return _modelMat;

    _modelMat = glm::mat4(1.0f);
    _modelMat = glm::translate(_modelMat, _position);

    _modelMat *= glm::toMat4(_rotate);
    
    _modelMat = glm::scale(_modelMat, _scale);
    
    _dirtyTransform = false;

    return _modelMat;
}

glm::mat4 Node::getWorldMat() noexcept {
	if (!_dirtyWorldTransform && !_dirtyTransform) return _worldMat;
	if (_parent.expired()) return getModelMat();

	auto parentMat = _parent->getWorldMat();
	auto modelMat = getModelMat();

	_worldMat = parentMat * modelMat;

	_dirtyWorldTransform = false;

	return _worldMat;
}

//
NodeType Node::getNodeType() const noexcept {
	return _type;
}

bool Node::isEnabled() {
	return _enabled;
}

void Node::setEnabled(bool val) {
	for(auto& child: _childs)
		child->setEnabled(val);
	_enabled = val;
}

bool Node::isDied() const {
	return _this.expired();
}
