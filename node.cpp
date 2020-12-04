#include "node.h"

#include <glm/gtc/type_ptr.hpp>

Node::Node(NodeType type) noexcept
    : _type(type)
    , _modelMat ( glm::mat4(1.0f) )
    , _rotate   ( glm::quat() )
    , _position ( glm::vec3(0.0f, 0.0f, 0.0f) )
    , _scale    ( glm::vec3(1.0f, 1.0f, 1.0f) )
    , _dirtyTransform(true)
{  }

void Node::setScale(const glm::vec3& scale) noexcept
{ _scale = scale; _dirtyTransform = true; }

glm::vec3 Node::getScale() const noexcept
{ return _scale; }

void Node::setRotate(const glm::vec3& axis, const GLfloat angle) noexcept
{ _rotate = glm::angleAxis(angle, glm::normalize(axis)); _dirtyTransform = true; }

void Node::setRotate(const glm::vec3& angels) noexcept
{ _rotate = glm::quat(angels); _dirtyTransform = true; }

glm::quat Node::getRotate() const noexcept
{ return _rotate; }

void Node::setPosition(const glm::vec3& position) noexcept
{ _position = position; _dirtyTransform = true; }

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
//	for(auto & node = )
}

void Node::unvalidateWorldMat() noexcept {
	for(auto & node : _childs)
		node->unvalidateWorldMat();
	_dirtyWorldTransform = true;
}
