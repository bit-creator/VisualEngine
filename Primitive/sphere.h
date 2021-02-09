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

#include <cmath>
#include <memory>
#include <unordered_set>


#include "../geometry.h"

#include "../object3d.h"

class Sphere : public Geometry
{
	struct Vertex
	{
		glm::vec3			_coord;
		glm::vec2			_texCoord;
	};

	private:
		GLuint                                                          _subdiv;


        std::vector<Vertex>	                                            _vertices;
        std::unique_ptr<std::vector<glm::uvec3>>                        _indices;

    public:
        explicit Sphere(GLuint subdivision) noexcept;
        virtual ~Sphere() noexcept override;

        void setupBuffers() noexcept override;
        std::vector<Intersection> rayCast(Ray ray) const override;
        
    private:
        // void flipAndPush() noexcept;
        void refreshUV();
        void div(GLuint sub) noexcept;
        std::array<glm::uvec3, 4> divTriangle(glm::uvec3 triangle);
};

glm::vec2 genSphereUV(glm::vec3 c);
