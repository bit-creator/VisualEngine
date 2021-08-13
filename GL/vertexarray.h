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

#include <array>
#include <bitset>
#include <optional>

#include "globject.h"

enum class Attribute
{
   ATTRIB_POSITION = 0,
   ATTRIB_NORMAL,
   ATTRIB_TANGENT,
   ATTRIB_BITANGENT,
   ATTRIB_COLOR,
   ATTRIB_TEX
};

constexpr static int NUM_ATTRIBUTES = 6;

class VertexArray : public GLObject {
private:
	std::array < std::optional < Attribute >, NUM_ATTRIBUTES >                   _atributes;
	std::bitset < NUM_ATTRIBUTES >												 _hash;

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
    std::size_t getAttribHash() const;

private:
    GLuint getAttribSize(Attribute attr) const noexcept;
    GLuint getAttribDataType(Attribute attr) const noexcept;
    GLuint getAttribLocation(Attribute attr) const noexcept;
};

#endif //  VERTEXARRAY_H
