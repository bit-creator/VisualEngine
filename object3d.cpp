#include "object3d.h"

Object3D::Object3D() noexcept
    : Node(NodeType::NODE_OBJECT)
    , _material ( std::make_shared<Material>() )
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

std::vector<Intersection> Object3D::rayCastGeom(Ray ray) {
	return _geom->rayCast(ray);
}
