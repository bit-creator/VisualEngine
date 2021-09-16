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
	, _intensity(npos)
	, _angle(0.0)
	, _color(0.0, 0.0, 0.0, 0.0)
{  }

Light& Light::operator =(const Light &oth) noexcept {
}

Entity::reference Light::create(Entity::reference parent) {
	auto ref = Engine::engine().getScene()->lights.capture(parent);
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

void Light::initialize(size_t intensity, float angle, Color color) {
//	if (_color != glm::vec4(0.0, 0.0, 0.0, 0.0)) {
//		MESSAGE("reinitializing light, be carefull");
//	}
	_intensity = intensity;
	_angle = angle;
	_color = color;
}

void Light::setupPoint(size_t intensity, Color color) {
	decrementNumOfLights();
		_type = LightType::POINT;
	incrementNumOfLights();

	initialize(intensity, 0.0, color);
}

void Light::setupDir(Color color) {
	decrementNumOfLights();
		_type = LightType::DIRECTIONAL;
	incrementNumOfLights();

	initialize(npos, 0.0, color);
}

void Light::setupSpot(size_t intensity, float angle, Color color) {
	decrementNumOfLights();
		_type = LightType::SPOT;
	incrementNumOfLights();

	initialize(intensity, angle, color);
}

void Light::setAngle(float angle) {
	_angle = angle;
}

float Light::getAngle() const {
	return _angle;
}

void Light::setIntensity(size_t intensity) {
	_intensity = intensity;
}

void Light::initializeUniforms(ShaderProgram &prog, size_t index) {
}

size_t Light::getIntensity() const {
	return _intensity;
}

void Light::incrementNumOfLights() {
	switch(_type) {
	case LightType::DIRECTIONAL: Engine::scene()->lights._numDir++;   break;
	case LightType::POINT:		 Engine::scene()->lights._numPoint++; break;
	case LightType::SPOT:		 Engine::scene()->lights._numSpot++;  break;
	}
}

void Light::decrementNumOfLights() {
	switch(_type) {
	case LightType::DIRECTIONAL: Engine::scene()->lights._numDir--;   break;
	case LightType::POINT:		 Engine::scene()->lights._numPoint--; break;
	case LightType::SPOT:		 Engine::scene()->lights._numSpot--;  break;
	}
}
