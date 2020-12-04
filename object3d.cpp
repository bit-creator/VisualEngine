#include "object3d.h"

Object3D::Object3D() noexcept
    : Node(NodeType::NODE_OBJECT)
    , VAO       (  )
    , VBO       ( GL_ARRAY_BUFFER )
    , EBO       ( GL_ELEMENT_ARRAY_BUFFER ) 
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
{ return _geom; }
