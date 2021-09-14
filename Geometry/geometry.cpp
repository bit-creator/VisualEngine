#include "geometry.h"
#include <bitset>

Geometry::Geometry() noexcept    
	: _numVertex   (0)
	, _numIndex    (0)
    , _conectionMode ( GL_TRIANGLES )
{  }

Geometry::Geometry(const Geometry& oth) noexcept
	: _numVertex   ( oth._numVertex )
	, _numIndex    ( oth._numIndex )
	, _conectionMode ( oth._conectionMode )
	, VAO          (  )
	, VBO          (  )
	, EBO          (  )
{
	MESSAGE("Geometry COPY constructor called")
}

Geometry::Geometry(Geometry&& oth) noexcept
	: _numVertex   ( oth._numVertex )
	, _numIndex    ( oth._numIndex )
	, _conectionMode ( oth._conectionMode )
	, VAO          (  )
	, VBO          (  )
	, EBO          (  )
{
	MESSAGE("Geometry constructor called")
}

Geometry::~Geometry() noexcept { MESSAGE("Geometry destructor called") }


void Geometry::setNum(size_t index, size_t vertex) noexcept {
	_numIndex = index;
	_numVertex = vertex;
}

size_t Geometry::getNumIndices() const noexcept{
	return _numIndex;
}

size_t Geometry::getNumVertexes() const noexcept {
	return _numVertex;
}

bool Geometry::hasIndexes() const noexcept {
	return _numIndex != 0;
}

void Geometry::bindBuffers() noexcept {
    if(hasIndexes()) EBO.bind();
    VAO.bind();
}

void Geometry::unbindBuffers() noexcept {
    VAO.unbind();
    if(hasIndexes()) EBO.unbind();
}

void Geometry::setPoligonConnectMode(const GLenum mode) noexcept {
	_conectionMode = mode;
}

const GLenum Geometry::getPoligonConnectMode() const noexcept {
	return _conectionMode;
}

bool Geometry::hasTexCoord() const noexcept {
	return VAO.hasAttribute(Attribute::ATTRIB_TEX);
}


size_t Geometry::getAttributeHash() noexcept {
	return VAO.getAttribHash();
}
