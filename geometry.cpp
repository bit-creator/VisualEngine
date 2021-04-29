#include "geometry.h"
#include <bitset>

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

size_t Geometry::getNumIndices() const noexcept{
	return _numIndex;
}

size_t Geometry::getNumVertexes() const noexcept {
	return _numVertex;
}

bool Geometry::hasIndexes() const noexcept {
	return _useIndex;
}

void Geometry::bindBuffers() noexcept {
    if(_useIndex) EBO.bind();
    VAO.bind();
}

void Geometry::unbindBuffers() noexcept {
    VAO.unbind();
    if(_useIndex) EBO.unbind();
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
	std::bitset<NUM_ATTRIBUTES> 		hash;

	hash.set((int)Attribute::ATTRIB_BITANGENT, VAO.hasAttribute(Attribute::ATTRIB_BITANGENT));
	hash.set((int)Attribute::ATTRIB_COLOR,     VAO.hasAttribute(Attribute::ATTRIB_COLOR));
	hash.set((int)Attribute::ATTRIB_NORMAL,    VAO.hasAttribute(Attribute::ATTRIB_NORMAL));
	hash.set((int)Attribute::ATTRIB_POSITION,  VAO.hasAttribute(Attribute::ATTRIB_POSITION));
	hash.set((int)Attribute::ATTRIB_TANGENT,   VAO.hasAttribute(Attribute::ATTRIB_TANGENT));
	hash.set((int)Attribute::ATTRIB_TEX,       VAO.hasAttribute(Attribute::ATTRIB_TEX));

	return hash.to_ullong();
}
