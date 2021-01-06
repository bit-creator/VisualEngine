/**
 * @file geometry.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <memory>

#include "GL/buffer.h"
#include "GL/vertexarray.h"

class Geometry
{
    private:         //  Num of elements
        size_t                                                  _numVertex;
        size_t                                                  _numIndex;
        bool                                                    _useIndex;
        GLenum                                                  _conectionMode;

    protected:          //  OpenGL Buffers
        VertexArray                                             VAO;
        Buffer                                                  VBO;
        Buffer                                                  EBO;

    public:
        Geometry() noexcept;
        virtual ~Geometry() noexcept;

        size_t getNumIndices() const noexcept;
        size_t getNumVertexes() const noexcept;
        
        void setPoligonConnectMode(const GLenum) noexcept;
        const GLenum getPoligonConnectMode() const noexcept;
        
        bool hasIndexes() const noexcept;
        bool hasTexCoord() const noexcept;

        void bindBuffers() noexcept;
        void unbindBuffers() noexcept;
        
        virtual void setupBuffers() noexcept =0;

    protected:
        void setNum(size_t index, size_t vertex) noexcept;
};

using GeometryPtr = std::shared_ptr < Geometry >;

#endif // GEOMETRY_H
