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

#include "GL/shaderprogram.h"

using colour_t = glm::vec3;
using normal_t = glm::vec3;
using vertex_t = std::shared_ptr<glm::vec3>;

/**
 * @brief 
 * 
 * 
 * @default colour: white (1.0, 1.0, 1.0, 1.0)
 * 
 */
class Object3D
{
    protected:
        colour_t                       _colour;      

    public:
        Object3D() noexcept;
        Object3D(colour_t colour) noexcept;
        // Object3D(GLfloat R, GLfloat G, GLfloat B, GLfloat A) noexcept;
        Object3D(const Object3D& oth) noexcept;
        Object3D(Object3D&& oth) noexcept;
        virtual ~Object3D() noexcept;

        Object3D& operator =(const Object3D& oth) noexcept;
        Object3D& operator =(Object3D&& oth) noexcept;

        virtual void render(const ShaderProgram& program) const noexcept =0;
    private:
        virtual void setupBuffers() const noexcept =0;
};

#endif // OBJECT3D_H