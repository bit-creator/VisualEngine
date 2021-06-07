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

class Light :
	public Node
//	public MultiSharedCreator<Light, Node>
{
private:
	LightType							_type;
	Color								_color;

public:
	Light(LightType type);

	static std::shared_ptr<Light> create(LightType type);

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

using LightPtr = std::shared_ptr < Light >;

#endif /* LIGHT_H_ */
