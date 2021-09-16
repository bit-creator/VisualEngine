#include "vertexarray.h"

VertexArray::VertexArray() noexcept {
}

VertexArray::~VertexArray() noexcept {
}

void VertexArray::bind() noexcept {
	glBindVertexArray(_object); HANDLE_GL_ERROR();
}

void VertexArray::unbind() noexcept {
	glBindVertexArray(0); HANDLE_GL_ERROR();
}

void VertexArray::enable(Attribute attr) noexcept {
	glEnableVertexAttribArray(getAttribLocation(attr)); HANDLE_GL_ERROR();
	_enabled[int(attr)] = true;
}

void VertexArray::enable(uint32_t attr) noexcept {
	glEnableVertexAttribArray(attr); HANDLE_GL_ERROR();
	_enabled[attr] = true;
}

void VertexArray::enableAll() noexcept {
    for(int i = 0; i < NUM_ATTRIBUTES; ++i)
        if(_atributes[i]) enable(i);
}

void VertexArray::disable(Attribute attr) noexcept {
	glDisableVertexAttribArray(getAttribLocation(attr)); HANDLE_GL_ERROR();
	_enabled[int(attr)] = false;
}

void VertexArray::disable(uint32_t attr) noexcept {
	glDisableVertexAttribArray(attr); HANDLE_GL_ERROR();
	_enabled[attr] = false;
}

void VertexArray::disableAll() noexcept {
    for(int i = 0; i < NUM_ATTRIBUTES; ++i)
        if(_atributes[i]) disable(i);
}

GLuint VertexArray::getAttribSize(Attribute attr) const noexcept {
	return (attr == Attribute::ATTRIB_TEX ? 2 : 3);
}

GLuint VertexArray::getAttribDataType(Attribute attr) const noexcept {
	return GL_FLOAT;
}

std::size_t VertexArray::getAttribHash() const {
	return _enabled.to_ullong();
}

GLuint VertexArray::getAttribLocation(Attribute attr) const noexcept {
	return static_cast<int>(attr);
}

void VertexArray::addAttribute(Attribute attr, GLsizei stride, GLsizei offset) noexcept {
    glVertexAttribPointer(
        getAttribLocation(attr), getAttribSize(attr), getAttribDataType(attr),
        GL_FALSE, stride, (GLvoid*)offset); HANDLE_GL_ERROR();

    _atributes[getAttribLocation(attr)] = true;
}

bool VertexArray::hasAttribute(Attribute attr) const noexcept {
	return static_cast<bool>(_atributes[getAttribLocation(attr)]);
}
