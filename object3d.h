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
#include <glm/gtx/quaternion.hpp>

#include "material.h"
#include "geometry.h"

#include "GL/buffer.h"
#include "GL/vertexarray.h"
#include "GL/shaderprogram.h"

using Vector      = glm::vec3;

/**
 * @brief 
 * 
 * 
 * @default colour: white (1.0, 1.0, 1.0, 1.0)
 * 
 */
class Object3D
{
    private:
        GeometryPtr                                             _geom;  

    protected:          //  OpenGL Buffers
        VertexArray                                             VAO;
        Buffer                                                  VBO;
        Buffer                                                  EBO;

    protected:          //  Material & position
        glm::mat4                                               _modelMat;
        MaterialPtr                                             _material;
        glm::quat                                               _rotate;
        Vector                                                  _position;
        Vector                                                  _scale;
        bool                                                    _dirtyTransform;      

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
        glm::quat getRotate() const noexcept;

        void setScale(const glm::vec3& scale) noexcept;
        glm::vec3 getScale() const noexcept;

        void setPosition(const glm::vec3& position) noexcept;
        glm::vec3 getPosition() const noexcept;

        void setGeometry(GeometryPtr geometry) noexcept;
        GeometryPtr getGeometry() const noexcept;

        glm::mat4 getModelMat() noexcept;

        void render(const ShaderProgram& program) noexcept;
};

#endif // OBJECT3D_H