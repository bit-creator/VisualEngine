#include "triangle.h"

Triangle::Triangle() noexcept
    : Object3D()
    , _normal(glm::vec3(0.0f, 0.0f, 0.0f))
    , _vert_A(glm::vec3(0.0f, 0.0f, 0.0f))
    , _vert_B(glm::vec3(0.0f, 0.0f, 0.0f))
    , _vert_C(glm::vec3(0.0f, 0.0f, 0.0f))
{ setupBuffers(); }

Triangle::Triangle(vertex_t vert_A, vertex_t vert_B, vertex_t vert_C) noexcept
    : Object3D()
    , _vert_A(vert_A)
    , _vert_B(vert_B)
    , _vert_C(vert_C)
{ calculateNormal(); setupBuffers(); }

Triangle& Triangle::operator =(const Triangle& oth) noexcept
{ 
    if(&oth == this) return *this;
    _colour = oth._colour;
    _normal = oth._normal;
    _vert_A = oth._vert_A;
    _vert_B = oth._vert_B;
    _vert_C = oth._vert_C;

    return *this;
}
Triangle& Triangle::operator =(Triangle&& oth) noexcept
{  
    if(&oth == this) return *this;
    _colour = std::move(oth._colour);
    _normal = std::move(oth._normal);
    _vert_A = std::move(oth._vert_A);
    _vert_B = std::move(oth._vert_B);
    _vert_C = std::move(oth._vert_C);

    return *this;
}

Triangle::~Triangle() noexcept
{ glDeleteVertexArrays(1, &VAO); glDeleteBuffers(1, &VBO); }

void Triangle::setupBuffers() const noexcept
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glm::vec3 vertices[] = {
        _vert_A, _vert_B, _vert_C
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Triangle::render(const ShaderProgram& program) const noexcept
{
    program.enable();

    auto color = getColor();

    auto offset = getOffset();

    glm::mat3 mat = getModelMat();

    program.setUniform("uColor", color.r, color.g, color.b, color.w );
    program.setUniform("uModelMat", mat);
    program.setUniform("uPosition", offset);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Triangle::calculateNormal() noexcept
{
    _normal = glm::normalize(glm::cross(_vert_B - _vert_A, _vert_C - _vert_A));
}