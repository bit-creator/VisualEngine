#include "buffer.h"

Buffer::Buffer(GLuint type) noexcept
    : _type(type)
{ auto ID = getID(); glGenBuffers(1, &ID); }

Buffer::~Buffer() noexcept
{ glDeleteBuffers(1, &getID()); }

void Buffer::bind() noexcept
{ glBindBuffer(_type, getID()); }

void Buffer::unbind() noexcept
{ glBindBuffer(_type, 0); }

void Buffer::loadRawData(GLvoid* data) noexcept
{ glBufferData(_type, sizeof(data), data, GL_STATIC_DRAW); }

