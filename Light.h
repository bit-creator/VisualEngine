/*
 * Light.h
 *
 *  Created on: Dec 8, 2020
 *      Author: bit_creator
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include <algorithm>

#include "entity.h"
#include "Color.h"

enum class LightType
{
	DIRECTIONAL,
	POINT,
	SPOTS
};

class Light : public Entity {
private:
	LightType							_type;
	Color								_color;

protected:
	Light();

	Light(const Light& oth) noexcept =delete;
	Light& operator=(Light&&) noexcept = delete;

// copy
	Light& operator =(const Light& oth) noexcept;

public:
	Light(Light&&) noexcept =default;					// Need for pool construction "in place"
    ~Light() noexcept =default;

    static reference
    create(reference parent = reference::root());

    Entity::reference copy() override;
	void destroy() override;

	LightType getType() noexcept;

	void setColor(const Color& color);
	Color getColor() const;

	template < typename NodeT >
	friend class AbstractNodePool;
	friend class LightPool;
};

#endif /* LIGHT_H_ */
