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
#include "Color.h"

enum class LightType
{
	LIGHT_DIRECTIONAL,
	LIGHT_POINT,
	LIGHT_SPOTS
};

class Light : public Node {
private:
	LightType							_type;
	Color								_color;

public:
//	using reference = std::shared_ptr<Light>;
//    using reference = Node::reference;

	Light(LightType type);

	static reference create(LightType type);

	LightType getType() noexcept;

	void setColor(const Color& color);

	Color getColor() const;

};

class LightDirectional : public Light {
public:
	LightDirectional() noexcept
		: Light(LightType::LIGHT_DIRECTIONAL)
	{  }


};

std::string getLightsName(const int index);

//using LightPtr = Light::reference;

#endif /* LIGHT_H_ */
