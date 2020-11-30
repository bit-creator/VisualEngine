/**
 * @file cube.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>

#include "../geometry.h"

class Cube : public Geometry
{
    public:
        Cube() noexcept;
        virtual ~Cube() noexcept override;

        void setupBuffers() noexcept override;
};


#endif // CUBE_H
