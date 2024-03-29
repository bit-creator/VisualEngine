/**
 * @file Rect.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef RECT_H
#define RECT_H

#include <glm/glm.hpp>

#include "../geometry.h"

class Rect : public Geometry {
public:
	Rect() noexcept;
    virtual ~Rect() noexcept override;

    void setupBuffers() noexcept override;
	std::vector<Intersection> rayCast(Ray ray) const override;
};

#endif // RECT_H
