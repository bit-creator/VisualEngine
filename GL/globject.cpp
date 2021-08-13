/*
 * globject.cpp
 *
 *  Created on: 16 ���. 2021 �.
 *      Author: IAbernikhin
 */

#include "globject.h"

GLObject::GLObject(Creator creator, Deleter deleter)
	:  _object(creator())
	, _deleter(deleter)
{  }

GLObject::~GLObject() noexcept {
	_deleter(_object); HANDLE_GL_ERROR();
}

ObjectID& GLObject::getID() const noexcept {
	return _object;
}

