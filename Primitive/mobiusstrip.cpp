#include "mobiusstrip.h"


MobiusStrip::MobiusStrip(GLuint subdiv_l) noexcept
    : Geometry()
    , _subdiv(subdiv_l)
    , _vertices ({ 
        parametric(0.0f, -1),
        parametric(0.0f, 1),
     })
{ 
    genMobiusStrip(); 
    setNum(0,  _vertices.size()); 
    setupBuffers(); 
}

MobiusStrip::~MobiusStrip() noexcept {  }

void MobiusStrip::setupBuffers() noexcept 
{
    VAO.bind();
    VBO.bind();

    VBO.loadData(_vertices, GL_STATIC_DRAW);
    
    VAO.addAttribute(Attribute::ATTRIB_POSITION, 3 * sizeof(GLfloat), 0);
    VAO.addAttribute(Attribute::ATTRIB_NORMAL, 3 * sizeof(GLfloat), 0);
    
    setPoligonConnectMode(GL_TRIANGLE_STRIP);

    VAO.enableAll();

    VBO.unbind();
    VAO.unbind();
}

void MobiusStrip::genMobiusStrip() noexcept
{
    GLfloat step = DOUBLE_PI / _subdiv;
    for(GLfloat rider = step; rider < DOUBLE_PI; rider += step )
    {
        _vertices.push_back (parametric (rider, -1));
        _vertices.push_back (parametric (rider, 1));
    }    
        _vertices.push_back (parametric (DOUBLE_PI, -1));
        _vertices.push_back (parametric (DOUBLE_PI, 1));    
}

glm::vec3 MobiusStrip::parametric(GLfloat u, GLfloat v) const noexcept
{
    if ( u < 0 || u > DOUBLE_PI ) 
    {
        std::cout << "Mobius parametric assertion failed: value no in range" << std::endl;
        std::raise(SIGTERM);
    }

    if ( v < -1 || v > 1 ) 
    {
        std::cout << "Mobius parametric assertion failed: value no in range" << std::endl;
        std::raise(SIGTERM);
    }

    return glm::vec3 (
        (1 + (v / 2) * cos(u / 2)) * cos(u),
        (1 + (v / 2) * cos(u / 2)) * sin(u),
        (v / 2) * sin(u)
    );
}

