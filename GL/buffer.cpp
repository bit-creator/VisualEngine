#include "buffer.h"

Buffer::Buffer(GLuint type) noexcept
    : GLObject(genBuff())
    , _type(type)
{  }

Buffer::~Buffer() noexcept {
	glDeleteBuffers(1, &getID()); HANDLE_GL_ERROR();
}

void Buffer::bind() noexcept {
	glBindBuffer(_type, getID()); HANDLE_GL_ERROR();
}

void Buffer::unbind() noexcept {
	glBindBuffer(_type, 0); HANDLE_GL_ERROR();
}

void Buffer::loadRawData(GLvoid* data, size_t size, GLenum usage) noexcept {
	glBufferData(_type, size, data, usage); HANDLE_GL_ERROR();
}

GLuint Buffer::genBuff() {
    GLuint ID;
    glGenBuffers(1, &ID); HANDLE_GL_ERROR();
    return ID;
}
