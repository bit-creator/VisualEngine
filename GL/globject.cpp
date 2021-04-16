/*
 * globject.cpp
 *
 *  Created on: 16 квіт. 2021 р.
 *      Author: IAbernikhin
 */

#include "globject.h"

GLObject::GLObject(ObjectID obj) noexcept
    : _object(obj)
{  }

GLObject::~GLObject() noexcept {
	HANDLE_GL_ERROR();
}

ObjectID& GLObject::getID() const noexcept {
	return _object;
}
