/*
 * NodePool.cpp
 *
 *  Created on: 3 черв. 2021 р.
 *      Author: IAbernikhin
 */

#include "AbstractEntityPool.h"
#include "engine.h"

ObjectPool::ObjectPool(int reserv)
	: AbstractNodePool(reserv)
{  }

Entity::reference ObjectPool::capture(Entity::reference parent) {
//	auto obj = _nextAvailable;
//	if(!obj->isDied()) {
//		MESSAGE("something very bad");
//	}
//
//	_nextAvailable = obj->_next;
//	obj->_parent = Entity::reference();
//	obj->_this = obj;

	return captureImpl(parent);

//	return obj;
}

void ObjectPool::release(Entity::reference ref) {
//	if(ref.expired()) {
//		MESSAGE("something very bad");
//	}
//
//	if(ref->isDied()) return;
//
//	ref->_this.kill();
//
//	ref->_next = _nextAvailable;
//	_nextAvailable = ref;

	releaseImpl(ref);
}

size_t ObjectPool::getMaxId() {
	return _maxId;
}

LightPool::LightPool(int reserv)
	: AbstractNodePool(reserv)
	, _num(0)
{  }

Entity::reference LightPool::capture(Entity::reference parent) {
//	auto obj = _nextAvailable;
//	if(!obj->isDied()) {
//		MESSAGE("something very bad");
//	}
//
//	_nextAvailable = obj->_next;
//	obj->_parent = Entity::reference();
//	obj->_this = obj;

	++_num;

//	return obj;
	return captureImpl(parent);
}

void LightPool::release(Entity::reference ref) {
//	if(ref.expired()) {
//		MESSAGE("something very bad");
//	}
//
//	if(ref->isDied()) return;

	--_num;

	releaseImpl(ref);
//	ref->_this.kill();
//
//	ref->_next = _nextAvailable;
//	_nextAvailable = ref;
}

size_t LightPool::capacity() {
	return _num;
}

NodePool::NodePool(int reserv) : AbstractNodePool(reserv) {
	_pool[0]._this = Entity::reference(0, EntityType::NODE);
	_pool[0]._parent = Entity::reference();

	_nextAvailable = Entity::reference(1, EntityType::NODE);

	_pastTheLast = 1;
}

Entity::reference NodePool::capture(Entity::reference parent) {
//	auto ref = _nextAvailable;
//
//	auto obj = ref.get<Node>();
//	if(!obj->isDied()) {
//		MESSAGE("something very bad");
//	}
//
//	_nextAvailable = obj->_next;
//	obj->_parent = Entity::reference();
//	obj->_this = ref;

//	return ref;

	return captureImpl(parent);
}

void NodePool::release(Entity::reference ref) {
//	if(ref.expired()) {
//		MESSAGE("something very bad");
//	}
//
//	if(ref->isDied()) return;
//
//	ref->_this.kill();

	if(ref == Engine::scene()->root()) {
		MESSAGE("root no deleted");
		return;
	}

	releaseImpl(ref);
//	ref->_next = _nextAva

}
