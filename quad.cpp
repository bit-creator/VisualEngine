#include "quad.h"

Quad::Quad(const vertex_t& first,
             const vertex_t& second,
             const vertex_t& third,
             const vertex_t& four) 
    // : _first(first, second, third)
    // , _second(second, third, four)
    : _vert_A(first)
    , _vert_B(second)
    , _vert_C(third)
    , _vert_D(four)
{ setupBuffers(); }

void Quad::render(const ShaderProgram& program) const noexcept
{
    // _first.render(program);
    // _second.render(program);

    program.enable();

    auto color = getColor();

    auto scale = getScale();

    auto offset = getOffset();

    glm::mat3 mat;

    glm::mat3 mRotate = generateRotateMatrix(getRotate());

    glm::mat3x3 mScale(scale.x, 0.,      0.,
                   0.,      scale.y, 0.,
                   0.,      0.,      scale.z);

    mat = mRotate * mScale;

    program.setUniform("Color", color.r, color.g, color.b, color.w );
    program.setUniform("mat", mat);
    program.setUniform("offset", offset);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Quad::setupBuffers() const noexcept
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    GLfloat vertices[] = {
        _vert_A -> x, _vert_A -> y, _vert_A -> z,  
        _vert_B -> x, _vert_B -> y, _vert_B -> z,
        _vert_C -> x, _vert_C -> y, _vert_C -> z,  
        _vert_B -> x, _vert_B -> y, _vert_B -> z,
        _vert_C -> x, _vert_C -> y, _vert_C -> z,
        _vert_D -> x, _vert_D -> y, _vert_D -> z,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}


