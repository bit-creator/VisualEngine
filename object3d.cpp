#include "object3d.h"
#include "engine.h"
#include <GL/glew.h>

Object3D::Object3D() noexcept
    : Entity(EntityType::OBJECT)
{  }

void Object3D::setMaterial(MaterialPtr material) noexcept
{ _material = material; }

MaterialPtr Object3D::getMaterial() const noexcept
{ return _material; }

void Object3D::setGeometry(GeometryPtr geometry) noexcept
{ _geom = geometry; }

GeometryPtr Object3D::getGeometry() const noexcept
{
	return _geom;
}

glm::vec4 Object3D::getColorKey() const {
	GLubyte id[sizeof(_ID)];
	memcpy(id, &_ID, sizeof(Object3D::ID_t));

	glm::vec4 res;

	switch (sizeof(ID_t)) {
	case 1: res = glm::vec4(id[0], 0.0, 0.0, 0.0);		 break;
	case 2: res = glm::vec4(id[0], id[1], 0.0, 0.0);	 break;
	case 3: res = glm::vec4(id[0], id[1], id[2], 0.0);	 break;
	case 4: res = glm::vec4(id[0], id[1], id[2], id[3]); break;
	default: ERROR("Object3D ID very big");
	};

	return res / 255.0f;
}

void Object3D::setClicable(bool clicable) {
	if(_clicable == clicable) return;

	auto& pool = Engine::engine().getScene()->objects;

	if(clicable) {
		if (pool._freeId.empty()) {
			_ID = ++pool._maxId;
		} else {
			_ID = pool._freeId.back();
			pool._freeId.pop_back();
		}
	} else {
		if(_ID == pool._maxId) --pool._maxId;
		else pool._freeId.push_back(_ID);

		resetID();
	}

	_clicable = clicable;
}

bool Object3D::isClicable() const {
	return _clicable;
}

Object3D& Object3D::operator =(const Object3D &oth) noexcept {
}

void Object3D::resetID() {
	_ID = 0;
}

Entity::reference Object3D::create(MaterialPtr material, GeometryPtr geometry, bool clicable) {
	auto ref = Engine::scene()->objects.capture();

	ref.get<Object3D>()->setMaterial(material);
	ref.get<Object3D>()->setGeometry(geometry);
	ref.get<Object3D>()->setClicable(clicable);
	return ref;
}

size_t Object3D::getID() const {
	return _ID;
}

Entity::reference Object3D::copy() {
}

void Object3D::destroy() {
	_parent->removeChild(_this);
	Engine::scene()->objects.release(_this);
}
