/*
 * Light.cpp
 *
 *  Created on: Dec 8, 2020
 *      Author: bit_creator
 */

#include "Light.h"
#include "engine.h"

Light::Light(LightType type)
	: Node(NodeType::NODE_LIGHT)
	, _type(type)
{
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

std::string getLightsName(const int index) {
	std::string patern = "uLights[%].";
	std::replace(patern.begin(), patern.end(), '%', (char)(index + '0'));
	return patern;
}

Node::reference Light::create(LightType type) {
	auto& pool = Engine::engine().lights;
	return Node::reference(pool.allocate(type), NodeType::NODE_LIGHT);
}
