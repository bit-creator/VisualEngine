/**
 * @file globject.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef GLOBJECT_H
#define GLOBJECT_H

#include <iostream>
#include <type_traits>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#define CHECK_ERROR() {	\
	auto res = glGetError(); \
	if(res != GL_NO_ERROR) { \
		std::cout << "FUNCTION: " << __func__ << "\tLINE: " << __LINE__ << '\t'; \
		std::cout << "|   ERROR   |" << res << '\n'; \
	}\
}

using ObjectID = const GLuint;

/**
 * @brief wrapper for openGl objects
 * 
 * @tparam create(void) 
 * @tparam clear(ObjectID) 
 */
class GLObject
{
    private:
        ObjectID                            _object;                      // ID current shader
    protected:
        /**
         * @brief Construct a new GLObject object 
         *        use tparam create()
         */
        explicit GLObject(ObjectID obj = 0) noexcept
            : _object(obj)
        {  }
        
        /**
         * @brief Construct a new GLObject object
         *        or replace current object
         *        use other object prohibited
         */
        GLObject(const GLObject&)  =delete;
        
        GLObject& 
        operator=(const GLObject&) =delete;

        GLObject(GLObject&&) =default;
        GLObject& operator=(GLObject&&) =default;

        
        /**
         * @brief Destroy the GLObject object
         *        use tparam clear()
         */
        ~GLObject() noexcept {
        	CHECK_ERROR();
        }
 
    public:
        /**
         * @brief get reference to ID
         * 
         * @return ID current object 
         */
        ObjectID&
        getID() const noexcept {
        	return _object;
        }
}; // GLObject

#endif // GLOBJECT_H
