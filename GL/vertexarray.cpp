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
{ glEnableVertexAttribArray(getAttribLocation(attr)); }

void VertexArray::enableAll() noexcept
{
    for(auto& attr : _atributes)
        if(attr) enable(*attr);
}

void VertexArray::disable(Attribute attr) noexcept
{ glDisableVertexAttribArray(getAttribLocation(attr)); }

void VertexArray::disableAll() noexcept
{
    for(auto& attr : _atributes)
        if(attr) disable(*attr); 
}

GLuint VertexArray::genVAO() noexcept
{ GLuint VAO; glGenVertexArrays(1, &VAO); return VAO; }

GLuint VertexArray::getAttribSize(Attribute attr) const noexcept
{ return (attr == Attribute::ATTRIB_TEX ? 2 : 3); }

GLuint VertexArray::getAttribDataType(Attribute attr) const noexcept
{ return GL_FLOAT; }

GLuint VertexArray::getAttribLocation(Attribute attr) const noexcept
{ return static_cast<int>(attr); }


void VertexArray::addAttribute(Attribute attr, GLsizei stride, GLsizei offset) noexcept{
    glVertexAttribPointer(
        getAttribLocation(attr), getAttribSize(attr), getAttribDataType(attr),
        GL_FALSE, stride, (GLvoid*)offset
    ); 
    _atributes[getAttribLocation(attr)] = attr;
}

bool VertexArray::hasAttribute(Attribute attr) const noexcept
{ return static_cast<bool>(_atributes[getAttribLocation(attr)]); }
