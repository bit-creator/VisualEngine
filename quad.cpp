#include "quad.h"

Quad::Quad(const vertex_t& first,
             const vertex_t& second,
             const vertex_t& third,
             const vertex_t& four) 
    // : _first(first, second, third)
    // , _second(second, third, four)
    : VBO(GL_ARRAY_BUFFER)
    , EBO(GL_ELEMENT_ARRAY_BUFFER)
    , _vert_A(first)
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
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Quad::setupBuffers() const noexcept
{
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);

    VBO.bind();
    EBO.bind();
    
    std::vector<glm::vec3> vertices = {
        *_vert_A, *_vert_B, *_vert_C, *_vert_D
    };

    std::vector<GLuint> indices = {
        1, 2, 3,
        2, 3, 4  
    };

    VBO.loadRawData(vertices.data());
    EBO.loadRawData(indices.data());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    VBO.unbind();
    EBO.unbind();

    glBindVertexArray(0);
}


