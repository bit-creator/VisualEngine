#include "vertexarray.h"

VertexArray::VertexArray() noexcept
    : GLObject(genVAO())
    , _atributes()
{ HANDLE_GL_ERROR(); }

VertexArray::~VertexArray() noexcept {
	glDeleteVertexArrays(1, &getID()); HANDLE_GL_ERROR();
}

void VertexArray::bind() noexcept {
	glBindVertexArray(getID()); HANDLE_GL_ERROR();
}

void VertexArray::unbind() noexcept {
	glBindVertexArray(0); HANDLE_GL_ERROR();
}

void VertexArray::enable(Attribute attr) noexcept {
	glEnableVertexAttribArray(getAttribLocation(attr)); HANDLE_GL_ERROR();
	_hash[int(attr)] = true;
}

void VertexArray::enableAll() noexcept {
    for(auto& attr : _atributes)
        if(attr) enable(*attr);
}

void VertexArray::disable(Attribute attr) noexcept {
	glDisableVertexAttribArray(getAttribLocation(attr)); HANDLE_GL_ERROR();
	_hash[int(attr)] = false;
}

void VertexArray::disableAll() noexcept {
    for(auto& attr : _atributes)
        if(attr) disable(*attr); 
}

GLuint VertexArray::genVAO() noexcept {
	GLuint VAO;
	glGenVertexArrays(1, &VAO); HANDLE_GL_ERROR();
	return VAO;
}

GLuint VertexArray::getAttribSize(Attribute attr) const noexcept {
	return (attr == Attribute::ATTRIB_TEX ? 2 : 3);
}

GLuint VertexArray::getAttribDataType(Attribute attr) const noexcept {
	return GL_FLOAT;
}

std::size_t VertexArray::getAttribHash() const {
	return _hash.to_ullong();
}

GLuint VertexArray::getAttribLocation(Attribute attr) const noexcept {
	return static_cast<int>(attr);
}

void VertexArray::addAttribute(Attribute attr, GLsizei stride, GLsizei offset) noexcept {
    glVertexAttribPointer(
        getAttribLocation(attr), getAttribSize(attr), getAttribDataType(attr),
        GL_FALSE, stride, (GLvoid*)offset); HANDLE_GL_ERROR();

    _atributes[getAttribLocation(attr)] = attr;
}

bool VertexArray::hasAttribute(Attribute attr) const noexcept {
	return static_cast<bool>(_atributes[getAttribLocation(attr)]);
}
