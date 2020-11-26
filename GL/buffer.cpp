#include "buffer.h"

Buffer::Buffer(GLuint type) noexcept
    : GLObject(genBuff())
    , _type(type)
{  }

Buffer::~Buffer() noexcept
{ glDeleteBuffers(1, &getID()); }

void Buffer::bind() noexcept
{ glBindBuffer(_type, getID()); }

void Buffer::unbind() noexcept
{ glBindBuffer(_type, 0); }

void Buffer::loadRawData(GLvoid* data, size_t size, GLenum usage) noexcept
{ glBufferData(_type, size, data, usage); }

GLuint Buffer::genBuff()
{
    GLuint ID;
    glGenBuffers(1, &ID);
    return ID;
}