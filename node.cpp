#include "node.h"
#include "object3d.h"
#include "engine.h"

#include <glm/gtc/type_ptr.hpp>

////////// Node::reference ///////////

Node::reference::reference()
: _offset(root), _type(NodeType::NODE_NODE)
{  }

Node::reference::reference(size_t offset, NodeType type)
	: _offset(offset), _type(type)
{  }

//Node* Node::reference::get() {
//	return _ref->get();
//}

bool Node::reference::isRoot() {
	return _offset == root;
}

bool Node::reference::isDied() {
	return _offset == died;
}

Node* Node::reference::operator ->() {
	switch(_type) {
	case NodeType::NODE_CAMERA: return Engine::engine().getScene()->getCamera();
	case NodeType::NODE_OBJECT: return ((dynamic_cast<Object3D*>(Engine::getPool(_type))) + _offset);
	case NodeType::NODE_LIGHT: return ((dynamic_cast<Light*>(Engine::getPool(_type))) + _offset);
	case NodeType::NODE_NODE: return ((dynamic_cast<Node*>(Engine::getPool(_type))) + _offset);
	};
	return nullptr;
}


/////////////// NODE //////////////

Node::Node() noexcept
	: Node(NodeType::NODE_NODE) {
}

Node::Node(NodeType type) noexcept
	: _childs({})
	, _parent()
    , _type(type)
    , _modelMat ( glm::mat4(1.0f) )
    , _rotate   ( glm::quat() )
    , _position ( glm::vec3(0.0f, 0.0f, 0.0f) )
    , _scale    ( glm::vec3(1.0f, 1.0f, 1.0f) )
    , _dirtyTransform(true)
	, _dirtyWorldTransform(true)
	, _enabled(true)
{  }

void Node::setScale(const glm::vec3& scale) noexcept {
	_scale = scale;
	_dirtyTransform = true;
	unvalidateWorldMat();
}

glm::vec3 Node::getScale() const noexcept {
	return _scale;
}

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
	if (_parent.isRoot()) return getModelMat();

//	auto parentMat = _parent.lock()->getWorldMat();
	auto parentMat = _parent->getWorldMat();
	auto modelMat = getModelMat();

	_worldMat = parentMat * modelMat;

	_dirtyWorldTransform = false;

	return _worldMat;
}

Node::Node(const Node &oth) noexcept
	: _parent()
	, _type(oth._type)
	, _modelMat(oth._modelMat)
	, _worldMat(oth._worldMat)
	, _rotate(oth._rotate)
	, _position(oth._position)
	, _scale(oth._scale)
	, _dirtyTransform(oth._dirtyTransform)
	, _dirtyWorldTransform(oth._dirtyWorldTransform)
	, _enabled(oth._enabled)
{
//	for(auto node : oth._childs)
//	{
//		auto cp = std::make_shared<Node>(*node);
//		addChild(cp);
//	}
}

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

void Node::unvalidateWorldMat() noexcept {
	for (auto & node : _childs)
		node->unvalidateWorldMat();

	if (!_dirtyWorldTransform)
	_dirtyWorldTransform = true;
}

void Node::addChild(Node::reference child) {
	if(!child->_parent.isRoot()){
//		child ->_parent.lock()->removeChild(child);
		child ->_parent->removeChild(child);
//		child -> _parent.reset();
//		child -> _parent = reference();
	}
	_childs.push_back(child);
//	child -> _parent = weak_from_this();
	child->_parent = _this;
//	child->_parent = referenceFromThis();    // Not Working Good

	child->_dirtyWorldTransform = true;
	child->_dirtyTransform = true;
}

void Node::removeChild(Node::reference child) {
	if(_childs.empty()) return;
//	_childs.remove_if([child = child](Node::reference ch){return ch.owner_before(child);});
	_childs.remove(child);
}

std::list < Node::reference >& Node::getChilds() {
	return _childs;
}

//std::list< Intersection >
//Node::rayCast(Ray ray) {
//	std::list< Intersection > result;
//	rayCastImpl(ray, result);
//	return result;
//}

Node::~Node() {
}

Node::reference Node::create(NodeType type) {
	auto& pool = Engine::engine().getScene()->nodes;
	reference ref = reference(pool.allocate(type), NodeType::NODE_NODE);
	ref->_this = ref;
	return ref;
}


// Not Working Good
Node::reference Node::referenceFromThis() const {
//	auto pool = Engine::getPool(_type);
//
//	switch(_type) {
//	case NodeType::NODE_LIGHT : {
//		auto concrPool = dynamic_cast<const Light*>(pool);
//		auto thisP = dynamic_cast<const Light*>(this);
//		return new LightRef((thisP - concrPool) / sizeof(concrPool));
//		break;
//	}
//
//	case NodeType::NODE_OBJECT : {
//		auto concrPool = dynamic_cast<const Object3D*>(pool);
//		auto thisP = dynamic_cast<const Object3D*>(this);
//		return new ObjectRef((thisP - concrPool) / sizeof(concrPool));
//		break;
//	}
//
//	case NodeType::NODE_CAMERA : {
//		return new CameraRef();
//		break;
//	}
//
//	case NodeType::NODE_NODE : {
//		return new NodeRef((this - pool) / sizeof(pool));
//		break;
//	}
//
//	default :
//		return new NullRef();
//	}
}


//void Node::rayCastImpl(Ray& ray, std::list< Intersection >& list) {
//	for(auto child : _childs) child->rayCastImpl(ray, list);
//}

Object3D* Node::search(int id) {
	Object3D* res = nullptr;
	for(auto child : _childs) {
		res = child->search(id);
		if(res) return res;
	} return res;
}
