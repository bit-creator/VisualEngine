/**
 * @file cone.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef CONE_H
#define CONE_H

#include "circle.h"

class Cone : public Circle
{
    public:
        explicit Cone(GLuint subdiv) noexcept;
        virtual ~Cone() noexcept override;

        void setupBuffers() noexcept override;

    private:
        void genFace();
        glm::vec3 getBaseNormal();

};

#endif // CONE_H
