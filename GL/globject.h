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
#include <functional>

#include <GL/glew.h>

#define DEBUG
#include "../Macro.hpp"

using ObjectID = const GLuint;

class GLObject {
private:
	using Creator = std::function < ObjectID(void) >;
	using Deleter = std::function < void(ObjectID&) >;

private:
	ObjectID                            _object;                      // ID current gl object
	Deleter								_deleter;					  // Deleter for gl object

protected:
	GLObject(Creator creator, Deleter deleter);

        
    GLObject(const GLObject&)  =delete;
    GLObject& operator=(const GLObject&) =delete;

    GLObject(GLObject&&) =default;
    GLObject& operator=(GLObject&&) =default;

    ~GLObject() noexcept;

public:
    ObjectID& getID() const noexcept;
}; // GLObject

#endif // GLOBJECT_H
