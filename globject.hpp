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
        explicit GLObject(ObjectID obj) noexcept
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
        ~GLObject() noexcept =default;
 
    public:
        /**
         * @brief get reference to ID
         * 
         * @return ID current object 
         */
        ObjectID&
        getID() const noexcept
        { return _object; }
}; // GLObject

#endif // GLOBJECT_H