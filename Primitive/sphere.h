/**
 * @file sphere.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <memory>
#include <unordered_set>

#include <boost/functional/hash.hpp>

#include "../geometry.h"

#include "../object3d.h"

class Sphere : public Geometry
{
    private:
        GLuint                                                          _subdiv;

        std::vector<glm::vec3>                                          _vertices;
        std::unique_ptr<std::vector<glm::uvec3>>                        _indices;

    public:
        explicit Sphere(GLuint subdivision) noexcept;
        ~Sphere() noexcept;

        void setupBuffers() noexcept override;
        
    private:
        // void flipAndPush() noexcept;
        void div(GLuint sub) noexcept;
        std::array<glm::uvec3, 4> divTriangle(glm::uvec3 triangle);
};