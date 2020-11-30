#include "cone.h"


Cone::Cone(GLuint subdiv) noexcept
    : Circle(subdiv)
{
    // _vertices.push_back(getBaseNormal());
    _vertices.push_back(glm::vec3(0., 0., 1.));

    if(subdiv == 1) 
    {
        _indices.push_back(glm::uvec3(3, 1, 0));
        _indices.push_back(glm::uvec3(3, 2, 0));
        _indices.push_back(glm::uvec3(3, 1, 2));
    }
    else genFace(); 
    setNum(_indices.size() * 3, _vertices.size());
    setupBuffers();
}

Cone::~Cone() noexcept {  }

void Cone::setupBuffers() noexcept 
{
    VAO.bind();
    VBO.bind();
    EBO.bind();

    VBO.loadData(_vertices, GL_STATIC_DRAW);
    EBO.loadData(_indices, GL_STATIC_DRAW);
    
    VAO.addAttribute(Attribute::ATTRIB_POSITION, 3 * sizeof(GLfloat), 0);
    // VAO.addAttribute(Attribute::ATTRIB_NORMAL, 3 * sizeof(GLfloat), 0);
    
    VAO.enableAll();

    VBO.unbind();
    VAO.unbind();
}

void Cone::genFace() 
{
    auto index = _indices.size() - 1;
    auto value = _vertices.size() / 2;
    size_t counter = 0;
    for (; counter != value; --index)
    {
        _indices.push_back ( glm::uvec3 (
            _vertices.size() - 1,
            _indices[index][0],
            _indices[index][1]
        ));

        _indices.push_back ( glm::uvec3 (
            _vertices.size() - 1,
            _indices[index][0],
            _indices[index][2]
        ));

        ++counter;
    }
}

glm::vec3 Cone::getBaseNormal() { 
    return glm::normalize (glm::cross (
        _vertices[1] - _vertices[0], 
        _vertices[2] - _vertices[0]
    ));
}


