/*
 * NodePool.cpp
 *
 *  Created on: 3 черв. 2021 р.
 *      Author: IAbernikhin
 */

#include "AbstractEntityPool.h"
#include "engine.h"

ObjectPool::ObjectPool(int reserv) : AbstractNodePool(reserv) {  }

Entity::reference ObjectPool::capture(void) {
	auto obj = _nextAvailable;
	if(!obj->isDied()) {
		MESSAGE("something very bad");
	}

	_nextAvailable = obj->_next;
	obj->_parent = Entity::reference();
	obj->_this = obj;

	return obj;
}

void ObjectPool::release(Entity::reference ref) {
	if(ref.expired()) {
		MESSAGE("something very bad");
	}

	if(ref->isDied()) return;

	ref->_next = _nextAvailable;
	_nextAvailable = ref;
}

size_t ObjectPool::getMaxId() {
	return _maxId;
}

LightPool::LightPool(int reserv)
	: AbstractNodePool(reserv)
	, _num(0)
{  }

Entity::reference LightPool::capture(void) {
	auto obj = _nextAvailable;
	if(!obj->isDied()) {
		MESSAGE("something very bad");
	}

	_nextAvailable = obj->_next;
	obj->_parent = Entity::reference();
	obj->_this = obj;

	++_num;

	return obj;
}

void LightPool::release(Entity::reference ref) {
	if(ref.expired()) {
		MESSAGE("something very bad");
	}

	if(ref->isDied()) return;

	--_num;

	ref->_next = _nextAvailable;
	_nextAvailable = ref;
}

size_t LightPool::capacity() {
	return _num;
}

NodePool::NodePool(int reserv) : AbstractNodePool(reserv) {
	_pool[0]._this = Entity::reference(0, EntityType::NODE);
	_pool[0]._parent = Entity::reference();

	_nextAvailable = Entity::reference(1, EntityType::NODE);
}

Entity::reference NodePool::capture(void) {
	auto ref = _nextAvailable;

	auto obj = ref.get<Node>();
	if(!obj->isDied()) {
		MESSAGE("something very bad");
	}

	_nextAvailable = obj->_next;
	obj->_parent = Entity::reference();
	obj->_this = ref;

	return ref;
}

void NodePool::release(Entity::reference ref) {
	if(ref.expired()) {
		MESSAGE("something very bad");
	}

	if(ref->isDied()) return;

	ref->_next = _nextAvailable;
	_nextAvailable = ref;
}
