/*
 * AbstractNodeRef.cpp
 *
 *  Created on: 7 черв. 2021 р.
 *      Author: iabernikhin
 */

#include "AbstractNodeRef.h"
#include "engine.h"

AbstractNodeRef::AbstractNodeRef(size_t offset) :
		_offset(offset) {
}

AbstractNodeRef::~AbstractNodeRef() {
}

ObjectRef::ObjectRef(size_t offset) :
		AbstractNodeRef(offset) {
}

ObjectRef::~ObjectRef() {
}

Node* ObjectRef::get() const {
	return Engine::getPool<Object3D>() + _offset;
}

LightRef::LightRef(size_t offset) :
		AbstractNodeRef(offset) {
}

LightRef::~LightRef() {
}

Node* LightRef::get() const {
	return Engine::getPool<Light>() + _offset;
}

NodeRef::NodeRef(size_t offset) :
		AbstractNodeRef(offset) {
}

NodeRef::~NodeRef() {
}

Node* NodeRef::get() const {
	return Engine::getPool<Node>() + _offset;
}

CameraRef::CameraRef() :
		AbstractNodeRef(0) {
}

CameraRef::~CameraRef() {
}

Node* CameraRef::get() const {
	return Engine::engine().getScene()->getCamera();
}

bool AbstractNodeRef::expired() const {
	return _offset == npos;
}

NullRef::NullRef() :
	AbstractNodeRef(npos) {
}

NullRef::~NullRef() {
}

Node* NullRef::get() const {
	std::cout << "get NULL reference to node" << std::endl;
	return nullptr;
}

AbstractNodeRef& AbstractNodeRef::operator =(const AbstractNodeRef &oth) {
	if(&oth == this) return *this;

	_offset = oth._offset;

	return *this;
}
