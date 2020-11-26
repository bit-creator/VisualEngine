/**
 * @file Rect.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef RECT_H
#define RECT_H

#include "../object3d.h"
#include "../GL/buffer.h"

class Rect : public Object3D
{
    private:
        mutable GLuint                  VAO;
        mutable Buffer                  VBO;
        mutable Buffer                  EBO;

    public:
        Rect();

        void render(const ShaderProgram& program) const noexcept;
    private:
        void setupBuffers() const noexcept;

};

#endif // RECT_H
