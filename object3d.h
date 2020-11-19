/**
 * @file Primitive3D.h
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

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "shaderprogram.h"

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
class Primitive3D
{
    protected:
        colour_t                       _colour;      

    public:
        Primitive3D() noexcept;
        Primitive3D(colour_t colour) noexcept;
        Primitive3D(GLfloat R, GLfloat G, GLfloat B, GLfloat A) noexcept;
        Primitive3D(const Primitive3D& oth) noexcept;
        Primitive3D(Primitive3D&& oth) noexcept;
        virtual ~Primitive3D() noexcept;

        Primitive3D& operator =(const Primitive3D& oth) noexcept;
        Primitive3D& operator =(Primitive3D&& oth) noexcept;

        void setColour(colour_t colour) noexcept;
        void setColour(GLfloat R, GLfloat G, GLfloat B, GLfloat A) noexcept;
        void setRed(GLfloat red) noexcept;
        void setGreen(GLfloat green) noexcept;
        void setBlue(GLfloat blue) noexcept;
        void setAlpha(GLfloat alpha) noexcept;

        const GLfloat& 
        red() const noexcept;
        const GLfloat& 
        green() const noexcept;
        const GLfloat& 
        blue() const noexcept;
        const GLfloat& 
        alpha() const noexcept;

        virtual void render(const ShaderProgram& program) const noexcept =0;
};

/**
 * @brief 
 * 
 * 
 * @default colour: white (1.0, 1.0, 1.0, 1.0)
 * @default normal:       (0.0, 0.0, 0.0);
 * @default vert_A:       (0.0, 0.0, 0.0);
 * @default vert_B:       (0.0, 0.0, 0.0);
 * @default vert_C:       (0.0, 0.0, 0.0);
 */
class Triangle : public Primitive3D
{
    private:
        mutable GLuint                          VAO;

    protected:
        normal_t                       _normal;
        vertex_t                       _vert_A;
        vertex_t                       _vert_B;
        vertex_t                       _vert_C;

    public:
        /**
         * @brief Construct a new Triangle object
         *        default (constructor) allocate vertex
         *        other derived default
         */
        Triangle() noexcept;
        Triangle(const Triangle& oth) noexcept;
        Triangle(Triangle&& oth) noexcept;
        
        Triangle(colour_t color, normal_t normal, vertex_t vert_A, 
            vertex_t vert_B, vertex_t vert_C) noexcept;

        Triangle(normal_t normal, vertex_t vert_A, 
            vertex_t vert_B, vertex_t vert_C) noexcept;
        
        Triangle(vertex_t vert_A, vertex_t vert_B, vertex_t vert_C) noexcept;

        Triangle& operator =(const Triangle& oth) noexcept;
        Triangle& operator =(Triangle&& oth) noexcept;    

        virtual ~Triangle() noexcept override;

        // impl vertex, normal geter

        void render(const ShaderProgram& shader) const noexcept override;
        void setupBuffers() const noexcept;

    private:
        /**
         * @brief claculate normal use 3 vertex
         */
        void calculateNormal() noexcept;
};


#endif // OBJECT3D_H