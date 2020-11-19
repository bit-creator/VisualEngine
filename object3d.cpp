#include "object3d.h"

Object3D::Object3D() noexcept
    : _colour(glm::vec4(1.0, 1.0, 1.0, 1.0))
{  }

Object3D::Object3D(colour_t colour) noexcept
    : _colour(colour)
{  }

// Object3D::Object3D(GLfloat R, GLfloat G,
//     GLfloat B, GLfloat A = 1.0) noexcept
//         : _colour(glm::vec4(R, G, B, A))
// {  }

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

// void Object3D::setColour(colour_t colour) noexcept 
// { _colour = colour; }

// void Object3D::setColour(GLfloat R, GLfloat G, GLfloat B, GLfloat A = 1.0) noexcept
// { _colour = glm::vec4(R, G, B, A);  }

// void Object3D::setRed(GLfloat red) noexcept 
// { _colour.r = red; }

// void Object3D::setGreen(GLfloat green) noexcept 
// { _colour.g = green; }

// void Object3D::setBlue(GLfloat blue) noexcept 
// { _colour.b = blue; }

// void Object3D::setAlpha(GLfloat alpha) noexcept 
// { _colour[3] = alpha; }

// const GLfloat& Object3D::red() const noexcept
// { return _colour[0]; }

// const GLfloat& Object3D::green() const noexcept
// { return _colour[1]; }

// const GLfloat& Object3D::blue() const noexcept
// { return _colour[2]; }

// const GLfloat& Object3D::alpha() const noexcept
// { return _colour[3]; }

