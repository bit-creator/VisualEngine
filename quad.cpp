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
    program.enable();

    auto color = getColor();

    auto offset = getOffset();

    glm::mat3 mat = getModelMat();

    program.setUniform("uColor", color.r, color.g, color.b, color.w );
    program.setUniform("uModelMat", mat);
    program.setUniform("uPosition", offset);

    EBO.bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    EBO.unbind();
}

void Quad::setupBuffers() const noexcept
{
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);

    VBO.bind();
    EBO.bind();
    
    std::vector<glm::vec3> vertices = {
        _vert_A, _vert_B, _vert_C, _vert_D
    };

    std::vector<GLuint> indices = {
        0, 1, 2,
        1, 2, 3  
    };


    VBO.loadRawData(vertices.data(), vertices.size() * 3 * sizeof(GLfloat));
    EBO.loadRawData(indices.data(), indices.size() * sizeof(GLuint));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    VBO.unbind();

    glBindVertexArray(0);
}


