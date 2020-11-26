#include "vertexarray.h"

VertexArray::VertexArray() noexcept
    : GLObject(genVAO())
    , _atributes({std::nullopt, std::nullopt, std::nullopt})
{  }

VertexArray::~VertexArray() noexcept
{ glDeleteVertexArrays(1, &getID()); }

void VertexArray::bind() noexcept
{ glBindVertexArray(getID()); }

void VertexArray::unbind() noexcept
{ glBindVertexArray(0); }

void VertexArray::enable() noexcept
{ glEnableVertexAttribArray(0); }

GLuint VertexArray::genVAO() noexcept
{ GLuint VAO; glGenVertexArrays(1, &VAO); return VAO; }

GLuint VertexArray::getAttribSize(Attribute attr) noexcept
{ return 3; }

GLuint VertexArray::getAttribDataType(Attribute attr) noexcept
{ return GL_FLOAT; }


void VertexArray::addAttribute(Attribute attr, GLsizei stride, GLsizei offset) noexcept{
    glVertexAttribPointer(
        0, getAttribSize(attr), getAttribDataType(attr), GL_FALSE, stride, (GLvoid*)offset
    ); 
    _atributes[static_cast<int>(attr)] = attr;
}

bool VertexArray::hasAttribute(Attribute attr)
{ return static_cast<bool>(_atributes[static_cast<int>(attr)]); }