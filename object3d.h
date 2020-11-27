/**
 * @file Object3D.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <memory>

#include <glm/glm.hpp>

#include "material.h"

#include "GL/buffer.h"
#include "GL/vertexarray.h"
#include "GL/shaderprogram.h"

using Vector      = glm::vec3;
using Quaternion  = glm::vec4;

/**
 * @brief 
 * 
 * 
 * @default colour: white (1.0, 1.0, 1.0, 1.0)
 * 
 */
class Object3D
{
    protected:          //  OpenGL Buffers
        VertexArray                                             VAO;
        Buffer                                                  VBO;
        Buffer                                                  EBO;

    protected:          //  Material & position
        MaterialPtr                                             _material;      
        Quaternion                                              _rotate;
        Vector                                                  _offset;
        Vector                                                  _scale;

    private:         //  Num of elements
        size_t                                                  _numVertex;
        size_t                                                  _numIndex;
        bool                                                    _useIndex;

    public:
        Object3D() noexcept;
        Object3D(MaterialPtr material) noexcept;
        // Object3D(const Object3D& oth) noexcept;
        // Object3D(Object3D&& oth) noexcept;
        virtual ~Object3D() noexcept;

        // Object3D& operator =(const Object3D& oth) noexcept =default;
        // Object3D& operator =(Object3D&& oth) noexcept =default;

        void setMaterial(MaterialPtr material) noexcept;
        MaterialPtr getMaterial() const noexcept; 
        
        void setRotate(const glm::vec3& axis, const GLfloat angle) noexcept;
        Quaternion getRotate() const noexcept;

        void setScale(const glm::vec3& scale) noexcept;
        glm::vec3 getScale() const noexcept;

        void setOffset(const glm::vec3& offset) noexcept;
        glm::vec3 getOffset() const noexcept;

        size_t getNumIndices() const noexcept;
        size_t getNumVertexes() const noexcept;
        bool hasIndexes() const noexcept;

        glm::mat3 getModelMat() const noexcept;

        void render(const ShaderProgram& program) noexcept;

    protected:
        void setNum(size_t index, size_t vertex) noexcept;

        virtual void setupBuffers() noexcept =0;
};

glm::mat3x3 generateRotateMatrix(Quaternion rotate) noexcept;

#endif // OBJECT3D_H