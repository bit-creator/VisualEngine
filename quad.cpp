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
    program.enable();

    auto color = getColor();

    auto offset = getOffset();

    glm::mat3 mat = getModelMat();

    program.setUniform("uColor", color.r, color.g, color.b, color.w );
    program.setUniform("uModelMat", mat);
    program.setUniform("uPosition", offset);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Quad::setupBuffers() const noexcept
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    VBO.bind();
    EBO.bind();
    
    std::vector<glm::vec3> vertices = {
        _vert_A, _vert_B, _vert_C, _vert_D
    };

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


