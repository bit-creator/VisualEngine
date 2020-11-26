#include "rect.h"

Rect::Rect() 
    : VBO(GL_ARRAY_BUFFER)
    , EBO(GL_ELEMENT_ARRAY_BUFFER)
{ setupBuffers(); }

void Rect::render(const ShaderProgram& program) const noexcept
{
    program.enable();

    auto color = getColor();

    auto offset = getOffset();

    glm::mat3 mat = getModelMat();

    program.setUniform("uColor", color.r, color.g, color.b, color.w );
    program.setUniform("uModelMat", mat);
    program.setUniform("uPosition", offset);
    program.setUniform("uLightDir", glm::vec3(0., 0., -1.) * mat);

    EBO.bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    EBO.unbind();
}

void Rect::setupBuffers() const noexcept
{
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);

    VBO.bind();
    EBO.bind();
    
    glm::vec3 vertices[] = {
        glm::vec3(1., 1., 0.), 
        glm::vec3(-1., 1., 0.), 
        glm::vec3(1., -1., 0.), 
        glm::vec3(-1., -1., 0.),  
    };

    GLuint indices[] = {
        0, 1, 2,
        1, 2, 3  
    };


    VBO.loadData(vertices, GL_STATIC_DRAW);
    EBO.loadData(indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    VBO.unbind();

    glBindVertexArray(0);
}


