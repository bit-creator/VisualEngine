#include "object3d.h"
#include "engine.h"
#include <GL/glew.h>

Object3D::Object3D() noexcept
    : Node(NodeType::NODE_OBJECT)
	, _ID(0)
{  }

Object3D::Object3D(MaterialPtr material) noexcept
    : Object3D()
{ _material = material; }

Object3D::Object3D(MaterialPtr material, GeometryPtr geometry) noexcept
	: Object3D()
{
	_material = material;
	_geom     = geometry;
}

Object3D::~Object3D() noexcept 
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

Object3D::Object3D(const Object3D &oth) noexcept
	: Node(oth)
	, _geom(oth._geom)
	, _ID(oth._ID)
	, _material(oth._material)
	{
}

void Object3D::rayCastImpl(Ray &ray, std::list<Intersection> &list) {
	Node::rayCastImpl(ray, list);

	Ray localRay;
	localRay.setOrigin(glm::inverse(getWorldMat()) * glm::vec4(ray.getOrigin(), 1.0));
	localRay.setDirection(glm::inverse(getWorldMat()) * glm::vec4(ray.getDirection(), 0.0));

	auto intersections = _geom->rayCast(localRay);

	for (auto intersec : intersections) {
		intersec._obj = this;
		list.push_back(intersec);
	}
}

//Object3D::ID_t Object3D::getID() const {
//	return _ID;
//}

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

//void Object3D::setID(Object3D::ID_t id) {
//	_ID = id;
//}

void Object3D::setClicable(bool clicable) {
	if(_clicable == clicable) return;

	auto& pool = Engine::engine().objects;

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

void Object3D::resetID() {
	_ID = 0;
}

Object3D* Object3D::search(int id) {
	if (id == _ID) return this;
	return nullptr;
}

