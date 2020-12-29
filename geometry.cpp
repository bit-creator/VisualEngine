#include "geometry.h"

Geometry::Geometry() noexcept    
	: _numVertex   (0)
	, _numIndex    (0)
	, _useIndex    (false)
    , _conectionMode ( GL_TRIANGLES )
    , VAO          (  )
    , VBO          ( GL_ARRAY_BUFFER )
    , EBO          ( GL_ELEMENT_ARRAY_BUFFER )
{  }

Geometry::~Geometry() noexcept {  }

void Geometry::setNum(size_t index, size_t vertex) noexcept {
	_numIndex = index;
	_numVertex = vertex;
	_useIndex = index == 0 ? false : true;
}

size_t Geometry::getNumIndices() const noexcept
{ return _numIndex; }

size_t Geometry::getNumVertexes() const noexcept
{ return _numVertex;}

bool Geometry::hasIndexes() const noexcept
{ return _useIndex; }

void Geometry::bindBuffers() noexcept
{
    if(_useIndex) EBO.bind();
    VAO.bind();
}

void Geometry::unbindBuffers() noexcept
{
    VAO.unbind();
    if(_useIndex) EBO.unbind();
}

void Geometry::setPoligonConnectMode(const GLenum mode) noexcept
{ _conectionMode = mode; }

const GLenum Geometry::getPoligonConnectMode() const noexcept
{
	return _conectionMode;
}

bool Geometry::hasTexCoord() const noexcept {
	return VAO.hasAttribute(Attribute::ATTRIB_TEX);
}
