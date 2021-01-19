/*
 * Crystal.h
 *
 *  Created on: Jan 18, 2021
 *      Author: bit_creator
 */

#ifndef PRIMITIVE_CRYSTAL_H_
#define PRIMITIVE_CRYSTAL_H_

#include <vector>

#include <glm/glm.hpp>

#include "../geometry.h"

enum class FacetingType {
	Simple
};

class Crystal final : public Geometry {
private:
	struct Vertex {
		glm::vec3    _pos;
		glm::vec3	 _normal;
	};

	FacetingType												_type;
    GLuint                                                      _angles;

    std::vector<Vertex>	                                        _vertices;
    std::vector<glm::uvec3>                                     _indices;

public:
	Crystal(FacetingType type, GLuint angles) noexcept;
	virtual ~Crystal() noexcept override;

	void setupBuffers() noexcept override;

private:
	void genSimple();

	void genFigure(const float rad);
};

#endif /* PRIMITIVE_CRYSTAL_H_ */
