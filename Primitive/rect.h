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

class Rect : public Geometry
{
    public:
        Rect() noexcept;
        ~Rect() noexcept;

        void setupBuffers() noexcept override;

};

#endif // RECT_H
