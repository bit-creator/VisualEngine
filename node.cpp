#include "node.h"

#include <glm/gtc/type_ptr.hpp>

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

void Node::setScale(const glm::vec3& scale) noexcept
{
	_scale = scale;
	_dirtyTransform = true;
	unvalidateWorldMat();
}

glm::vec3 Node::getScale() const noexcept
{ return _scale; }

void Node::setRotate(const glm::vec3& axis, const GLfloat angle) noexcept
{
	_rotate = glm::angleAxis(angle, glm::normalize(axis));
	_dirtyTransform = true;
	unvalidateWorldMat();
}

void Node::setRotate(const glm::vec3& angels) noexcept
{
	_rotate = glm::quat(angels);
	_dirtyTransform = true;
	unvalidateWorldMat();
}

glm::quat Node::getRotate() const noexcept
{ return _rotate; }

void Node::setPosition(const glm::vec3& position) noexcept
{
	_position = position;
	_dirtyTransform = true;
	unvalidateWorldMat();
}

glm::vec3 Node::getPosition() const noexcept
{ return _position; }

glm::mat4 Node::getModelMat() noexcept
{
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

	auto parentMat = _parent.lock()->getWorldMat();
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
{
	for(auto node : oth._childs)
	{
		auto cp = std::make_shared<Node>(*node);
		addChild(cp);
	}
}

NodeType Node::getNodeType() const noexcept {
	return _type;
}

bool Node::isEnabled() {
	return _enabled;
}

void Node::setEnabled(bool val) {
	_enabled = val;
}

void Node::unvalidateWorldMat() noexcept {
	for (auto & node : _childs)
		node->unvalidateWorldMat();

	if (!_dirtyWorldTransform)
	_dirtyWorldTransform = true;
}

void Node::addChild(NodePtr child) {
	if(!child->_parent.expired()){
		child ->_parent.lock()->removeChild(child);
		child -> _parent.reset();
	}
	_childs.push_back(child);
	child -> _parent = weak_from_this();
	child->_dirtyWorldTransform = true;
	child->_dirtyTransform = true;
}

void Node::removeChild(NodePtr child) {
	if(_childs.empty()) return;
	_childs.remove_if([child = child](NodePtr ch){return ch.owner_before(child);});
}

std::list<std::shared_ptr<Node> >& Node::getChilds() {
	return _childs;
}
