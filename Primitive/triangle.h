/**
 * @file triangle.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/glm.hpp>

#include "../geometry.h"

class Triangle : public Geometry
{      
    protected:
        glm::vec3                       _vert_A;
        glm::vec3                       _vert_B;
        glm::vec3                       _vert_C;

    public:
        Triangle() noexcept;
        
        Triangle(const glm::vec3& vert_A, const glm::vec3& vert_B, const glm::vec3& vert_C) noexcept;

        virtual ~Triangle() noexcept override;

        void setupBuffers() noexcept override;
        glm::vec3 calculateNormal() noexcept;
};


#endif // TRIANGLE_H