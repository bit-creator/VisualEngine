/**
 * @file vertexarray.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <map>
#include <optional>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include "globject.hpp"

enum class Attribute
{
   ATTRIB_POSITION = 0,
   ATTRIB_NORMAL = 1,
   ATTRIB_COLOR = 2,
   ATTRIB_TEX = 3
};

class VertexArray : public GLObject {
private:
	std::array < std::optional < Attribute >, 4 >                   _atributes;

public:
	VertexArray() noexcept;
    ~VertexArray() noexcept;

    void bind() noexcept;
    void unbind() noexcept;
    void enable(Attribute attr) noexcept;
    void enableAll() noexcept;
    void disable(Attribute attr) noexcept;
    void disableAll() noexcept;

    void addAttribute(Attribute attr, GLsizei stride, GLsizei offset) noexcept;

    bool hasAttribute(Attribute attr) const noexcept;

private:
    GLuint genVAO() noexcept;
    GLuint getAttribSize(Attribute attr) const noexcept;
    GLuint getAttribDataType(Attribute attr) const noexcept;
    GLuint getAttribLocation(Attribute attr) const noexcept;
};

#endif //  VERTEXARRAY_H
