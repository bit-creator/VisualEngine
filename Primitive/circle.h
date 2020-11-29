/**
 * @file circle.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include <memory>
#include <vector>
#include <cmath>

#include <glm/glm.hpp>

#include "../geometry.h"

class Circle : public Geometry
{
    private:
        GLuint                                                          _subdiv;

        std::vector<glm::vec3>                                          _vertices;
        std::vector<glm::uvec3>                                         _indices;

    public:
        explicit Circle(GLuint subdiv) noexcept;
        ~Circle() noexcept;
    
        void setupBuffers() noexcept override;

    private:
        void div(GLuint sub) noexcept;
        void firstDiv() noexcept;
        void divTriangle(glm::uvec3 triangle) noexcept;

};


#endif // CIRCLE_H