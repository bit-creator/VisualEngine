#include "rect.h"

Rect::Rect() noexcept
    : Geometry()
{ setNum(0, 4); setupBuffers(); }

Rect::~Rect() noexcept {  }

void Rect::setupBuffers() noexcept
{
   	float vertices[] = {
			-1.0f, -1.0f,  0.0f, 0.0f,
   			-1.0f,  1.0f,  0.0f, 1.0f,
   	         1.0f, -1.0f,  1.0f, 0.0f,
   	         1.0f,  1.0f,  1.0f, 1.0f
   	};
    
    VAO.bind();
    VBO.bind();
    EBO.bind();

    VBO.loadData(vertices, GL_STATIC_DRAW);
    
    VAO.addAttribute(Attribute::ATTRIB_POSITION, 4 * sizeof(GLfloat), 0);
    VAO.addAttribute(Attribute::ATTRIB_TEX, 4 * sizeof(GLfloat), 2 * sizeof(GLfloat));
    
    setPoligonConnectMode(GL_TRIANGLE_STRIP);

    VAO.enableAll();

    VBO.unbind();
    VAO.unbind();
}

std::vector<Intersection> Rect::rayCast(
		Ray ray) const {
	return std::vector<Intersection>();
}
