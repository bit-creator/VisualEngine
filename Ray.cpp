/*
 * Ray.cpp
 *
 *  Created on: Jan 13, 2021
 *      Author: bit_creator
 */

#include "Ray.h"

Ray::Ray()
	: _direction(0.0f, 0.0f, 1.0f)
	, _origin(0.0f, 0.0f, 0.0f)
{  }

Ray::Ray(const glm::vec3 direction, const glm::vec3 origin)
	: _direction(direction)
	, _origin(origin)
{  }

Ray::~Ray() {
}

void Ray::setRay(glm::vec3 direction, glm::vec3 origin) {
	_direction = direction;
	_origin = origin;
}

void Ray::setDirection(glm::vec3 direction) {
	_direction = direction;
}

void Ray::setOrigin(glm::vec3 origin) {
	_origin = origin;
}

const glm::vec3 Ray::getDirection() const {
	return _direction;
}

const glm::vec3 Ray::getOrigin() const {
	return _origin;
}
