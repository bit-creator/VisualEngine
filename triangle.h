/**
 * @file triangle.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object3d.h"
#include "GL/shaderprogram.h"

class Triangle : public Object3D
{
    private:
        mutable GLuint                          VAO;
        mutable GLuint                          VBO;        

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
        
        // Triangle(colour_t color, normal_t normal, vertex_t vert_A, 
        //     vertex_t vert_B, vertex_t vert_C) noexcept;

        // Triangle(normal_t normal, vertex_t vert_A, 
        //     vertex_t vert_B, vertex_t vert_C) noexcept;
        
        Triangle(vertex_t vert_A, vertex_t vert_B, vertex_t vert_C) noexcept;

        Triangle& operator =(const Triangle& oth) noexcept;
        Triangle& operator =(Triangle&& oth) noexcept;    

        virtual ~Triangle() noexcept override;

        // impl vertex, normal geter

        void render(const ShaderProgram& shader) const noexcept override;
        void setupBuffers() const noexcept override;

    private:
        /**
         * @brief claculate normal use 3 vertex
         */
        void calculateNormal() noexcept;
};


#endif // TRIANGLE_H