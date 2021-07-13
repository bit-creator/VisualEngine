/*
 * Light.cpp
 *
 *  Created on: Dec 8, 2020
 *      Author: bit_creator
 */

#include "Light.h"
#include "engine.h"

Light::Light()
	: Entity(EntityType::LIGHT)
	, _type(LightType::DIRECTIONAL)
{  }

Light& Light::operator =(const Light &oth) noexcept {
}

Entity::reference Light::create() {
	auto ref = Engine::engine().getScene()->lights.capture();
	return ref;
}

Entity::reference Light::copy() {
}

LightType Light::getType() noexcept {
	return _type;
}

void Light::setColor(const Color &color) {
	_color = color;
}


Color Light::getColor() const {
	return _color;
}

void Light::destroy() {
}
