/**
 * @file mobiusstrip.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef MOBIUSSTRIP_H
#define MOBIUSSTRIP_H

#include <vector>
#include <csignal>
#include <cmath>

#include <glm/glm.hpp>

#include "../geometry.h"

static constexpr float PI = 3.14159265358979f;
static constexpr float DOUBLE_PI = 2 * PI;

class MobiusStrip : public Geometry
{
    private:
        GLuint                                                          _subdiv;

        std::vector<glm::vec3>                                          _vertices;

    public:
        MobiusStrip(GLuint subdiv_l) noexcept;
        virtual ~MobiusStrip() noexcept override;
        
        void setupBuffers() noexcept override;

    private:
        void genMobiusStrip() noexcept;
        glm::vec3 parametric(GLfloat u, GLfloat v) const noexcept; 
};

#endif // MOBIUSSTRIP_H
