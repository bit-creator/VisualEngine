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

void VertexArray::enable(Attribute attr) noexcept
{ glEnableVertexAttribArray(static_cast<int>(attr)); }

void VertexArray::enableAll() noexcept
{
    for(auto& attr : _atributes)
        if(attr) enable(*attr);
}

void VertexArray::disable(Attribute attr) noexcept
{ glDisableVertexAttribArray(static_cast<int>(attr)); }

void VertexArray::disableAll() noexcept
{
    for(auto& attr : _atributes)
        if(attr) disable(*attr); 
}

GLuint VertexArray::genVAO() noexcept
{ GLuint VAO; glGenVertexArrays(1, &VAO); return VAO; }

GLuint VertexArray::getAttribSize(Attribute attr) const noexcept
{ return 3; }

GLuint VertexArray::getAttribDataType(Attribute attr) const noexcept
{ return GL_FLOAT; }


void VertexArray::addAttribute(Attribute attr, GLsizei stride, GLsizei offset) noexcept{
    glVertexAttribPointer(
        static_cast<int>(attr), getAttribSize(attr), getAttribDataType(attr),
        GL_FALSE, stride, (GLvoid*)offset
    ); 
    _atributes[static_cast<int>(attr)] = attr;
}

bool VertexArray::hasAttribute(Attribute attr) const noexcept
{ return static_cast<bool>(_atributes[static_cast<int>(attr)]); }