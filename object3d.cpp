#include "object3d.h"

Primitive3D::Primitive3D() noexcept
    : _colour(glm::vec4(1.0, 1.0, 1.0, 1.0))
{  }

Primitive3D::Primitive3D(colour_t colour) noexcept
    : _colour(colour)
{  }

Primitive3D::Primitive3D(GLfloat R, GLfloat G,
    GLfloat B, GLfloat A = 1.0) noexcept
        : _colour(glm::vec4(R, G, B, A))
{  }

Primitive3D::Primitive3D(const Primitive3D& oth) noexcept
    : _colour(oth._colour)
{  }

Primitive3D::Primitive3D(Primitive3D&& oth) noexcept
    : _colour(std::move(oth._colour))
{  }

Primitive3D::~Primitive3D() noexcept 
{  }

Primitive3D& Primitive3D::operator =(const Primitive3D& oth) noexcept
{ if(&oth != this) _colour = oth._colour; return *this; }

Primitive3D& Primitive3D::operator =(Primitive3D&& oth) noexcept
{ if(&oth != this) _colour = std::move(oth._colour); return *this; }

void Primitive3D::setColour(colour_t colour) noexcept 
{ _colour = colour; }

void Primitive3D::setColour(GLfloat R, GLfloat G, GLfloat B, GLfloat A = 1.0) noexcept
{ _colour = glm::vec4(R, G, B, A);  }

void Primitive3D::setRed(GLfloat red) noexcept 
{ _colour.r = red; }

void Primitive3D::setGreen(GLfloat green) noexcept 
{ _colour.g = green; }

void Primitive3D::setBlue(GLfloat blue) noexcept 
{ _colour.b = blue; }

void Primitive3D::setAlpha(GLfloat alpha) noexcept 
{ _colour[3] = alpha; }

const GLfloat& Primitive3D::red() const noexcept
{ return _colour[0]; }

const GLfloat& Primitive3D::green() const noexcept
{ return _colour[1]; }

const GLfloat& Primitive3D::blue() const noexcept
{ return _colour[2]; }

const GLfloat& Primitive3D::alpha() const noexcept
{ return _colour[3]; }

