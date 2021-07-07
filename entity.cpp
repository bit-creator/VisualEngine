#include "entity.h"
#include "object3d.h"
#include "engine.h"

#include <glm/gtc/type_ptr.hpp>

////////// Node::reference ///////////

Entity::reference::reference()
	: reference(npos, EntityType::NODE)
{  }

Entity::reference::reference(size_t offset, EntityType type)
	: _offset(offset), _type(type)
{  }

bool Entity::reference::expired() const {
	return _offset == npos;
}

void Entity::reference::kill() {
	_offset = npos;
}

Entity* Entity::reference::operator ->() {
	switch(_type) {
	case EntityType::CAMERA: return Engine::engine().getScene()->getCamera();
	case EntityType::OBJECT: return ((dynamic_cast<Object3D*>(Engine::getPool(_type))) + _offset);
	case EntityType::LIGHT:  return ((dynamic_cast<Light*>(Engine::getPool(_type))) + _offset);
	case EntityType::NODE:   return ((dynamic_cast<Node*>(Engine::getPool(_type))) + _offset);
	} return nullptr;
}

/////////////// NODE //////////////

// creation
Entity::Entity(EntityType type) noexcept
	: _enabled(true)
    , _type(type)
{
	_this.kill();
	_next.kill();
}

//void Entity::initialize() {
//
//}

// copy
//Entity::Entity(const Entity &oth) noexcept
//	: _parent()
//	, _enabled(oth._enabled)
//	, _type(oth._type)
//{  }


Entity& Entity::operator =(const Entity& oth) noexcept{

}


Entity::reference Entity::copy() {
	auto pool = Engine::engine().getScene()->getPool<Entity>();
}

// destruction
//Entity::~Entity() {
//}

//void Entity::deinitialize() {
//
//}

// tree
void Entity::addChild(Entity::reference child) {
	if(!child->_parent.expired()){
		child ->_parent->removeChild(child);
	}
	_childs.push_back(child);
	child->_parent = _this;

	child->transform._dirtyTransform = true;
}

void Entity::removeChild(Entity::reference child) {
	if(_childs.empty()) return;
	_childs.remove(child);
}

std::list < Entity::reference >& Entity::getChilds() {
	return _childs;
}

void Entity::unvalidateWorldMat() noexcept {
	for (auto & node : _childs)
		node->unvalidateWorldMat();

	if (!transform._dirtyWorldTransform)
		transform._dirtyWorldTransform = true;
}

glm::mat4 Entity::getWorldMat() noexcept {
	if (!transform._dirtyWorldTransform && !transform._dirtyTransform) return transform._worldMat;
	if (_parent.expired()) return transform.getModelMat();

	auto parentMat = _parent->getWorldMat();
	auto modelMat = transform.getModelMat();

	transform._worldMat = parentMat * modelMat;

	transform._dirtyWorldTransform = false;

	return transform._worldMat;
}

void Entity::update() {
	if(transform._dirtyTransform) unvalidateWorldMat();
}

//
EntityType Entity::getNodeType() const noexcept {
	return _type;
}

bool Entity::isEnabled() {
	return _enabled;
}

void Entity::setEnabled(bool val) {
	for(auto& child: _childs)
		child->setEnabled(val);
	_enabled = val;
}


bool Entity::isDied() const {
	return _this.expired();
}
