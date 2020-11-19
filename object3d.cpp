#include "object3d.h"

Object3D::Object3D() noexcept
    : _colour(glm::vec4(1.0, 1.0, 1.0, 1.0))
{  }

Object3D::Object3D(colour_t colour) noexcept
    : _colour(colour)
{  }

Object3D::Object3D(const Object3D& oth) noexcept
    : _colour(oth._colour)
{  }

Object3D::Object3D(Object3D&& oth) noexcept
    : _colour(std::move(oth._colour))
{  }

Object3D::~Object3D() noexcept 
{  }

Object3D& Object3D::operator =(const Object3D& oth) noexcept
{ if(&oth != this) _colour = oth._colour; return *this; }

Object3D& Object3D::operator =(Object3D&& oth) noexcept
{ if(&oth != this) _colour = std::move(oth._colour); return *this; }
