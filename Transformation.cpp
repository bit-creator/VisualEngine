/*
 * Transformation.cpp
 *
 *  Created on: 7 лип. 2021 р.
 *      Author: IAbernikhin
 */

#include "Transformation.h"

Transformation::Transformation()
	: _modelMat ( glm::mat4(1.0f) )
	, _rotate   ( glm::quat() )
	, _position ( glm::vec3(0.0f, 0.0f, 0.0f) )
	, _scale    ( glm::vec3(1.0f, 1.0f, 1.0f) )
	, _dirtyTransform(true)
	, _dirtyWorldTransform(true)
{  }

void Transformation::setRotate(const glm::vec3& axis, const float angle) noexcept {
	_rotate = glm::angleAxis(angle, glm::normalize(axis));
	_dirtyTransform = true;
}

void Transformation::setRotate(const glm::vec3& angels) noexcept {
	_rotate = glm::quat(angels);
	_dirtyTransform = true;
}

glm::quat Transformation::getRotate() const noexcept {
	return _rotate;
}

void Transformation::setScale(const glm::vec3& scale) noexcept {
	_scale = scale;
	_dirtyTransform = true;
}

glm::vec3 Transformation::getScale() const noexcept {
	return _scale;
}

void Transformation::setPosition(const glm::vec3& position) noexcept {
	_position = position;
	_dirtyTransform = true;
}

glm::vec3 Transformation::getPosition() const noexcept {
	return _position;
}


glm::mat4 Transformation::getModelMat() noexcept {
    if(!_dirtyTransform) return _modelMat;

    _modelMat = glm::mat4(1.0f);
    _modelMat = glm::translate(_modelMat, _position);

    _modelMat *= glm::toMat4(_rotate);

    _modelMat = glm::scale(_modelMat, _scale);

    _dirtyTransform = false;

    return _modelMat;
}
