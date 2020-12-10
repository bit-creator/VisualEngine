/*
 * Light.h
 *
 *  Created on: Dec 8, 2020
 *      Author: bit_creator
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include <algorithm>

#include "node.h"

enum class LightType
{
	LIGHT_DIRECTIONAL,
	LIGHT_POINT,
	LIGHT_SPOTS
};

class Light: public Node {
private:
	LightType							_type;
	glm::vec4							_color;

public:
	Light(LightType type);

	LightType getType() noexcept;

	void setColor(const glm::vec4& color);

	glm::vec4 getColor() const;

};

class LightDirectional : public Light {

public:
	LightDirectional() noexcept
		: Light(LightType::LIGHT_DIRECTIONAL)
	{  }

};

std::string getLightsName(const int index);

using LightPtr = std::shared_ptr < Light >;

#endif /* LIGHT_H_ */
