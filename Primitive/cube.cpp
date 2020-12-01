#include "cube.h"

Cube::Cube() noexcept
    : Geometry()
{ setNum(36, 8); setupBuffers(); }

Cube::~Cube() noexcept {  }

void Cube::setupBuffers() noexcept
{
    glm::vec3 vertices[] = {
        glm::vec3( 1.,  1.,  1.),   // 1
        glm::vec3( 0.,  1.,  0.),
        glm::vec3(-1.,  1.,  1.),   // 2
        glm::vec3( 0.,  1.,  0.),
        glm::vec3(-1.,  1., -1.),   // 3
        glm::vec3( 0.,  1.,  0.),
        glm::vec3( 1.,  1., -1.),   // 4
        glm::vec3( 0.,  1.,  0.),

        glm::vec3( 1., -1.,  1.),   // 5
        glm::vec3( 0., -1.,  0.),
        glm::vec3(-1., -1.,  1.),   // 6
        glm::vec3( 0., -1.,  0.),
        glm::vec3(-1., -1., -1.),   // 7
        glm::vec3( 0., -1.,  0.),
        glm::vec3( 1., -1., -1.),   // 8 
        glm::vec3( 0., -1.,  0.),
        
        glm::vec3( 1.,  1.,  1.),   // 1
        glm::vec3( 0.,  0.,  1.),
        glm::vec3(-1.,  1.,  1.),   // 2
        glm::vec3( 0.,  0.,  1.),
        glm::vec3(-1., -1.,  1.),   // 6
        glm::vec3( 0.,  0.,  1.),
        glm::vec3( 1., -1.,  1.),   // 5
        glm::vec3( 0.,  0.,  1.),
        
        glm::vec3(-1.,  1., -1.),   // 3
        glm::vec3( 0.,  0., -1.),
        glm::vec3( 1.,  1., -1.),   // 4
        glm::vec3( 0.,  0., -1.),
        glm::vec3( 1., -1., -1.),   // 8 
        glm::vec3( 0.,  0., -1.),
        glm::vec3(-1., -1., -1.),   // 7
        glm::vec3( 0.,  0., -1.),
        
        glm::vec3(-1.,  1.,  1.),   // 2
        glm::vec3(-1.,  0.,  0.),
        glm::vec3(-1.,  1., -1.),   // 3
        glm::vec3(-1.,  0.,  0.),
        glm::vec3(-1., -1., -1.),   // 7
        glm::vec3(-1.,  0.,  0.),
        glm::vec3(-1., -1.,  1.),   // 6
        glm::vec3(-1.,  0.,  0.),
        
        glm::vec3( 1.,  1.,  1.),   // 1
        glm::vec3( 1.,  0.,  0.),
        glm::vec3( 1.,  1., -1.),   // 4
        glm::vec3( 1.,  0.,  0.),
        glm::vec3( 1., -1., -1.),   // 8 
        glm::vec3( 1.,  0.,  0.),
        glm::vec3( 1., -1.,  1.),   // 5
        glm::vec3( 1.,  0.,  0.),
    };

    glm::uvec3 indices[] = {
        glm::uvec3(0, 1, 2),
        glm::uvec3(0, 2, 3),

        glm::uvec3(4, 5, 6),
        glm::uvec3(4, 6, 7),
        
        glm::uvec3(8, 9, 10),
        glm::uvec3(8, 10, 11),
        
        glm::uvec3(12, 13, 14),
        glm::uvec3(12, 14, 15),
        
        glm::uvec3(16, 17, 18),
        glm::uvec3(16, 18, 19),
        
        glm::uvec3(20, 21, 22),
        glm::uvec3(20, 22, 23)
    };

    VAO.bind();
    VBO.bind();
    EBO.bind();

    VBO.loadData(vertices, GL_STATIC_DRAW);
    EBO.loadData(indices, GL_STATIC_DRAW);
    
    VAO.addAttribute(Attribute::ATTRIB_POSITION, 6 * sizeof(GLfloat), 0);
    VAO.addAttribute(Attribute::ATTRIB_NORMAL, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));

    // VAO.addAttribute(Attribute::ATTRIB_POSITION, 3 * sizeof(GLfloat), 0);
    // VAO.addAttribute(Attribute::ATTRIB_NORMAL, 3 * sizeof(GLfloat), 0);

    VAO.enableAll();

    VBO.unbind();
    VAO.unbind();
}