#include "triangle.h"

Triangle::Triangle() noexcept
    : Object3D()
    , _normal(glm::vec3(0.0f, 0.0f, 0.0f))
    , _vert_A(std::make_shared<glm::vec3>(glm::vec3(0.0, 0.0f, 0.0f)))
    , _vert_B(std::make_shared<glm::vec3>(glm::vec3(0.0, 0.0f, 0.0f)))
    , _vert_C(std::make_shared<glm::vec3>(glm::vec3(0.0, 0.0f, 0.0f)))
{ setupBuffers(); }

Triangle::Triangle(const Triangle& oth) noexcept
    : Object3D(oth._colour)
    , _normal(oth._normal)
    , _vert_A(oth._vert_A)
    , _vert_B(oth._vert_B)
    , _vert_C(oth._vert_C)
{ setupBuffers(); }

Triangle::Triangle(Triangle&& oth) noexcept
    : Object3D(std::move(oth._colour))
    , _normal(std::move(oth._normal))
    , _vert_A(std::move(oth._vert_A))
    , _vert_B(std::move(oth._vert_B))
    , _vert_C(std::move(oth._vert_C))
{ setupBuffers(); }

// Triangle::Triangle(colour_t colour, normal_t normal,
//     vertex_t vert_A, vertex_t vert_B, vertex_t vert_C) noexcept
//         : Object3D(colour)
//         , _normal(normal)
//         , _vert_A(vert_A)
//         , _vert_B(vert_B)
//         , _vert_C(vert_C)
// {  }
// Triangle::Triangle(normal_t normal, vertex_t vert_A, vertex_t vert_B, vertex_t vert_C) noexcept
//     : Object3D()
//     , _normal(normal)
//     , _vert_A(vert_A)
//     , _vert_B(vert_B)
//     , _vert_C(vert_C)
// {  }

Triangle::Triangle(vertex_t vert_A, vertex_t vert_B, vertex_t vert_C) noexcept
    : Object3D()
    , _vert_A(vert_A)
    , _vert_B(vert_B)
    , _vert_C(vert_C)
{ calculateNormal(); }

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
{ glDeleteVertexArrays(1, &VBO); glDeleteBuffers(1, &VBO); }

void Triangle::setupBuffers() const noexcept
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    GLfloat vertices[] = {
        _vert_A -> x, _vert_A -> y, _vert_A -> z,  
        _vert_B -> x, _vert_B -> y, _vert_B -> z,
        _vert_C -> x, _vert_C -> y, _vert_C -> z,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Triangle::render(const ShaderProgram& shader) const noexcept
{
    shader.enable();

    shader.setUniform("Color", 1.0, 1.0, 1.0, 1.0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Triangle::calculateNormal() noexcept
{

}