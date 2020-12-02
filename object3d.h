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

#include "node.h"
#include "material.h"
#include "geometry.h"
#include "perspectivecamera.h"
#include "orthographiccamera.h"

#include "GL/buffer.h"
#include "GL/vertexarray.h"
#include "GL/shaderprogram.h"


/**
 * @brief 
 * 
 * 
 * @default colour: white (1.0, 1.0, 1.0, 1.0)
 * 
 */
class Object3D : public Node
{
    private:
        GeometryPtr                                             _geom;  

    protected:          //  OpenGL Buffers
        VertexArray                                             VAO;
        Buffer                                                  VBO;
        Buffer                                                  EBO;

    protected:          //  Material
        MaterialPtr                                             _material;

    public:
        Object3D() noexcept;
        Object3D(MaterialPtr material) noexcept;

        virtual ~Object3D() noexcept;

        void setGeometry(GeometryPtr geometry) noexcept;
        GeometryPtr getGeometry() const noexcept;

        void setMaterial(MaterialPtr material) noexcept;
        MaterialPtr getMaterial() const noexcept; 

        void render(const Camera& camera, ShaderProgram& program) noexcept;
};

#endif // OBJECT3D_H