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

#define CHECK_GL_ERROR() {	 								\
	if (auto res = glGetError( ); res != GL_NO_ERROR) {		\
		std::cout << "| GL_ERROR | "      					\
				  << "file | " << __FILE__					\
				  << " | method | " << __PRETTY_FUNCTION__	\
				  << " | line | " << __LINE__   			\
				  << " | " << glewGetErrorString(res)		\
				  << std::endl;								\
	} else {												\
															\
	}														\
}     														\

using ObjectID = const GLuint;

class GLObject {
private:
	ObjectID                            _object;                      // ID current shader

protected:
	explicit GLObject(ObjectID obj = 0) noexcept
    	: _object(obj)
	{  }
        
    GLObject(const GLObject&)  =delete;
    GLObject& operator=(const GLObject&) =delete;

    GLObject(GLObject&&) =default;
    GLObject& operator=(GLObject&&) =default;

    ~GLObject() noexcept {
    	CHECK_GL_ERROR();
    }
 
public:
    ObjectID& getID() const noexcept {
    	return _object;
    }
}; // GLObject

#endif // GLOBJECT_H
