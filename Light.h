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

#include "GL/shaderprogram.h"

enum class LightType {
	DIRECTIONAL,
	POINT,
	SPOT
};

class Light : public Entity {
private:
	static constexpr inline size_t npos = std::numeric_limits<size_t>::max();
private:
	LightType						_type;
	size_t 							_intensity;
	float 							_angle;
	Color							_color;

protected:
	Light();

	Light(const Light& oth) noexcept =delete;
	Light& operator=(Light&&) noexcept = delete;

// copy
	Light& operator =(const Light& oth) noexcept;

public:
	Light(Light&&) noexcept =default;					// Need for pool construction "in place"
    ~Light() noexcept =default;

private:
    void initialize(size_t intensity, float angle, Color color);
    void incrementNumOfLights();
    void decrementNumOfLights();

public:
    void setupPoint(size_t intensity, Color color);
    void setupDir(Color color);
    void setupSpot(size_t intensity, float angle, Color color);

    void initializeUniforms(ShaderProgram& prog, size_t index);

    static reference
    create(reference parent = reference::root());

    Entity::reference copy() override;
	void destroy() override;

	LightType getType() noexcept;

	void setColor(const Color& color);
	Color getColor() const;

	void setAngle(float angle);
	float getAngle() const;

	void setIntensity(size_t intensity);
	size_t getIntensity() const;


	template < typename NodeT >
	friend class AbstractNodePool;
	friend class LightPool;
};

#endif /* LIGHT_H_ */
