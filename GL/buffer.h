/**
 * @file buffer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include "globject.hpp"

class Buffer : public GLObject
{
    private:
        const GLuint                           _type;

    public:
        Buffer(GLuint type) noexcept;
        ~Buffer() noexcept;

        void bind() noexcept;
        void unbind() noexcept;
        void loadRawData(GLvoid* data, size_t size) noexcept;
    
    private:
        GLuint genBuff();
};

#endif // BUFFER_H