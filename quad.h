/**
 * @file quad.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef QUAD_H
#define QUAD_H

#include "object3d.h"
#include "GL/buffer.h"

class Quad : public Object3D
{
    private:
        // Triangle            _first;
        // Triangle            _second;

        mutable GLuint                  VAO;
        mutable GLuint                  VBO;

    protected:
        normal_t                       _normal;
        vertex_t                       _vert_A;
        vertex_t                       _vert_B;
        vertex_t                       _vert_C;
        vertex_t                       _vert_D;

    public:
        Quad(const vertex_t& first,
             const vertex_t& second,
             const vertex_t& third,
             const vertex_t& four);

        void render(const ShaderProgram& program) const noexcept;
    private:
        void setupBuffers() const noexcept;

};

#endif // QUAD_H
