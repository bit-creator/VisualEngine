#include "circle.h"

using indexArray    = std::vector<glm::uvec3>;
using indexArrayPtr = std::unique_ptr<indexArray>;

Circle::Circle(GLuint subdiv) noexcept
    : _subdiv(subdiv)
    , _vertices ({
        glm::vec3 (   0.0f,                 1.0f, 0.0f ), // upper vertex
        glm::vec3 ( - 3.0f * sqrt(3) / 6, - 0.5f, 0.0f ), // left  vertex
        glm::vec3 (   3.0f * sqrt(3) / 6, - 0.5f, 0.0f ), // right vertex
    })
    , _indices ({
        glm::uvec3(0, 1, 2)
    })
{
    if(--_subdiv > 0) firstDiv();
    if(--_subdiv > 0) div(_subdiv); 
    setNum(_indices.size() * 3,  _vertices.size()); 
    setupBuffers(); 
}

Circle::~Circle() noexcept {  }

void Circle::div(GLuint sub) noexcept
{
    if(--sub == 0) return;
    auto index = _indices.size() - 1;
    auto value = _vertices.size() / 2;
    size_t counter = 0;
    for (; counter != value; --index)
    {
        divTriangle(_indices[index]);
        ++counter;
    }
    div(sub);
}

void Circle::firstDiv() noexcept
{
    _vertices.push_back(glm::normalize(glm::vec3(
        (_vertices[0].x + _vertices[1].x) / 2,
        (_vertices[0].y + _vertices[1].y) / 2, 
        (_vertices[0].z + _vertices[1].z) / 2 
        )));


    _vertices.push_back(glm::normalize(glm::vec3(
        (_vertices[0].x + _vertices[2].x) / 2,
        (_vertices[0].y + _vertices[2].y) / 2, 
        (_vertices[0].z + _vertices[2].z) / 2 
        ))); 


    _vertices.push_back(glm::normalize(glm::vec3(
        (_vertices[2].x + _vertices[1].x) / 2,
        (_vertices[2].y + _vertices[1].y) / 2, 
        (_vertices[2].z + _vertices[1].z) / 2 
        )));

    _indices.push_back(glm::uvec3(5, 2, 1));
    _indices.push_back(glm::uvec3(4, 0, 2));
    _indices.push_back(glm::uvec3(3, 0, 1));
}

void Circle::divTriangle(glm::uvec3 triangle) noexcept
{
    _vertices.push_back (glm::normalize (glm::vec3 (
        ( _vertices[triangle[0]].x + _vertices[triangle[1]].x ) / 2,
        ( _vertices[triangle[0]].y + _vertices[triangle[1]].y ) / 2, 
        ( _vertices[triangle[0]].z + _vertices[triangle[1]].z ) / 2
        )));

    _vertices.push_back (glm::normalize (glm::vec3 (
        ( _vertices[triangle[0]].x + _vertices[triangle[2]].x ) / 2,
        ( _vertices[triangle[0]].y + _vertices[triangle[2]].y ) / 2,
        ( _vertices[triangle[0]].z + _vertices[triangle[2]].z ) / 2
        ))); 

    _indices.push_back(glm::uvec3(_vertices.size() -1, triangle[0], triangle[2]));
    _indices.push_back(glm::uvec3(_vertices.size() -2, triangle[0], triangle[1]));
}

void Circle::setupBuffers() noexcept 
{
    VAO.bind();
    VBO.bind();
    EBO.bind();

    VBO.loadData(_vertices, GL_STATIC_DRAW);
    EBO.loadData(_indices, GL_STATIC_DRAW);
    
    VAO.addAttribute(Attribute::ATTRIB_POSITION, 3 * sizeof(GLfloat), 0);
    VAO.addAttribute(Attribute::ATTRIB_NORMAL, 3 * sizeof(GLfloat), 0);
    
    VAO.enableAll();

    VBO.unbind();
    VAO.unbind();
}

std::pair < const std::vector<glm::vec3>&, const std::vector<glm::uvec3>& > 
Circle::extractData() noexcept
{ return std::make_pair(_vertices, _indices); }