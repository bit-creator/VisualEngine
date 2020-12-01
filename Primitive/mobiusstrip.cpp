#include "mobiusstrip.h"


MobiusStrip::MobiusStrip(GLuint subdiv_l) noexcept
    : Geometry()
    , _subdiv(subdiv_l)
    , _vertices ({ 
        parametric(U_MIN, V_MIN),
        parametric(U_MIN, V_MAX),
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
        _vertices.push_back (parametric (rider, V_MIN));
        _vertices.push_back (parametric (rider, V_MAX));
    }    
        _vertices.push_back (parametric (DOUBLE_PI, V_MIN));
        _vertices.push_back (parametric (DOUBLE_PI, V_MAX));    
}

glm::vec3 MobiusStrip::parametric(GLfloat u, GLfloat v) const noexcept
{
    if ( u < U_MIN || u > U_MAX ) 
    {
        std::cout << "Mobius parametric assertion failed: value no in range" << std::endl;
        std::raise(SIGTERM);
    }

    if ( v < V_MIN || v > V_MAX ) 
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

