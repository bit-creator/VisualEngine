/**
 * @file window.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <csignal>
#include <memory>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    using pointer   =       GLFWwindow*;
    using const_pointer = const pointer;

private:
    pointer                         _window;

    GLfloat                         _version;

    GLint                          _width;
    GLint                          _height;

    std::string                     _title;


public:
    Window() noexcept;
    Window(const GLfloat version) noexcept;
    Window(const GLint& width, const GLint& height) noexcept;
    Window(const std::string& title) noexcept;
    Window(const GLfloat version, const std::string& title) noexcept;

    Window(const GLfloat version,
           const GLint&   width,
           const GLint&   height) noexcept;

    Window(const GLint&       width,
           const GLint&       height,
           const std::string& title) noexcept;

    Window(const GLfloat     version,
           const GLint&       width,
           const GLint&       height,
           const std::string& title) noexcept;

    ~Window() noexcept;
    Window(const Window& other) = default;
    Window(Window&& other) = default;
    Window& operator=(const Window& other) = default;
    Window& operator=(Window&& other) = default;

    void setup() noexcept;

    const_pointer get() const noexcept;
    pointer       get() noexcept;

    operator pointer( ) const;
    operator pointer( );

    std::pair<int32_t, int32_t> 
    getWindowSize() const noexcept;


private:
    static void keyCallBack(pointer window, int key, int scancode, int action, int mode);
    static void mouseCallBack(pointer window, double x, double y);
    static void mouseClickCallBack(pointer window, int button, int action, int mode);
};

using WndPtr = GLFWwindow *;

#endif // WINDOW_HPP
