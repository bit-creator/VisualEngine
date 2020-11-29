#include "rect.h"

Rect::Rect() noexcept
    : Geometry()
{ setNum(0, 4); setupBuffers(); }

Rect::~Rect() noexcept {  }

void Rect::setupBuffers() noexcept
{
    glm::vec3 vertices[] = {
        glm::vec3(1., 1., 0.), 
        glm::vec3(-1., 1., 0.), 
        glm::vec3(1., -1., 0.), 
        glm::vec3(-1., -1., 0.),  
    };
    
    VAO.bind();
    VBO.bind();

    VBO.loadData(vertices, GL_STATIC_DRAW);
    
    VAO.addAttribute(Attribute::ATTRIB_POSITION, 3 * sizeof(GLfloat), 0);
    
    setPoligonConnectMode(GL_TRIANGLE_STRIP);

    VAO.enableAll();

    VBO.unbind();
    VAO.unbind();
}
