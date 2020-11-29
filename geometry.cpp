#include "geometry.h"

Geometry::Geometry() noexcept    
    : VAO       (  )
    , VBO       ( GL_ARRAY_BUFFER )
    , EBO       ( GL_ELEMENT_ARRAY_BUFFER ) 
{  }

Geometry::~Geometry() noexcept {  }

void Geometry::setNum(size_t index, size_t vertex) noexcept
{ _numIndex = index; _numVertex = vertex; _useIndex = index == 0 ? false : true; }

size_t Geometry::getNumIndices() const noexcept
{ return _numIndex; }

size_t Geometry::getNumVertexes() const noexcept
{ return _numVertex;}

bool Geometry::hasIndexes() const noexcept
{ return _useIndex; }

void Geometry::bindBuffers() noexcept
{
    EBO.bind();
    VAO.bind();
}

void Geometry::unbindBuffers() noexcept
{
    VAO.unbind();
    EBO.unbind();
}


