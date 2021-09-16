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

#include "RowGraphicObject.h"

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

class VertexArray: public RowGraphicObject <
	Creators::vertexArray,
	Deleters::vertexArray
> {
private:
	std::bitset < NUM_ATTRIBUTES >												 _atributes;
	std::bitset < NUM_ATTRIBUTES >												 _enabled;

public:
	VertexArray() noexcept;
	~VertexArray() noexcept;

    void bind() noexcept;
    void unbind() noexcept;
    void enable(Attribute attr) noexcept;
    void enableAll() noexcept;
    void disable(Attribute attr) noexcept;
    void disableAll() noexcept;

    void addAttribute(Attribute attr, int32_t stride, int32_t offset) noexcept;

    bool hasAttribute(Attribute attr) const noexcept;
    std::size_t getAttribHash() const;

private:
    uint32_t getAttribSize(Attribute attr) const noexcept;
    uint32_t getAttribDataType(Attribute attr) const noexcept;
    uint32_t getAttribLocation(Attribute attr) const noexcept;
    void enable(uint32_t attr) noexcept;
    void disable(uint32_t attr) noexcept;
};

#endif //  VERTEXARRAY_H
