#include "buffer.h"

Buffer::Buffer(GLuint type) noexcept
    : _type(type)
{  }


Buffer::~Buffer() noexcept {
}

void Buffer::bind() noexcept {
	glBindBuffer(_type, _object); HANDLE_GL_ERROR();
}

void Buffer::unbind() noexcept {
	glBindBuffer(_type, 0); HANDLE_GL_ERROR();
}

void Buffer::loadRawData(GLvoid* data, size_t size, GLenum usage) noexcept {
	glBufferData(_type, size, data, usage); HANDLE_GL_ERROR();
}

VertexBuffer::VertexBuffer()
	: Buffer(GL_ARRAY_BUFFER)
{  }

IndexBuffer::IndexBuffer()
	: Buffer(GL_ELEMENT_ARRAY_BUFFER)
{  }
