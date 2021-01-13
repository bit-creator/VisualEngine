/*
 * WaterBox.h
 *
 *  Created on: Jan 11, 2021
 *      Author: bit_creator
 */

#ifndef PRIMITIVE_WATERBOX_H_
#define PRIMITIVE_WATERBOX_H_

#include <array>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../geometry.h"

class WaterBox final : public Geometry {
private:
	struct Vertex {
		glm::vec3			_coord;
		glm::vec3			_normal;
		glm::vec2			_texCoord;
	};

	float 															_amplitude;
	float															_subdiv;

    std::vector<Vertex>	                                            _vertices;
    std::unique_ptr<std::vector<glm::uvec3>>						_indices;
public:
	WaterBox(float amplitude, float subdiv);
	virtual ~WaterBox() noexcept override;
	void setupBuffers() noexcept override;

private:
	void genSurface(GLuint sub);
	std::array<glm::uvec3, 4> divTriangle(glm::uvec3 triangle);
	void recalculateUV();
};

#endif /* PRIMITIVE_WATERBOX_H_ */
