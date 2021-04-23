#include "triangle.h"

Triangle::Triangle() noexcept
    : Geometry()
    , _vert_A(glm::vec3(1.0f, 0.0f, 0.0f))
    , _vert_B(glm::vec3(0.0f, 1.0f, 0.0f))
    , _vert_C(glm::vec3(0.0f, 0.0f, 1.0f))
{ setupBuffers(); setNum(0, 3); }

Triangle::Triangle(const glm::vec3& vert_A, const glm::vec3& vert_B, const glm::vec3& vert_C) noexcept
    : Geometry()
    , _vert_A(vert_A)
    , _vert_B(vert_B)
    , _vert_C(vert_C)
{ setupBuffers(); setNum(0, 3); }

Triangle::~Triangle() noexcept {  }

void Triangle::setupBuffers() noexcept
{
    glm::vec3 vertices[] = {
        _vert_A, _vert_B, _vert_C
    };
    
    VAO.bind();
    VBO.bind();

    VBO.loadData(vertices, GL_STATIC_DRAW);
    
    VAO.addAttribute(Attribute::ATTRIB_POSITION, 3 * sizeof(GLfloat), 0);

    VAO.enableAll();

    VBO.unbind();
    VAO.unbind();
}


glm::vec3 Triangle::calculateNormal() noexcept
{ return glm::normalize(glm::cross(_vert_B - _vert_A, _vert_C - _vert_A)); }