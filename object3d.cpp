#include "object3d.h"

Object3D::Object3D() noexcept
    : Node(NodeType::NODE_OBJECT)
//    , _material ( std::make_shared<Material>() )
{  }

Object3D::Object3D(MaterialPtr material) noexcept
    : Object3D()
{ _material = material; }

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
