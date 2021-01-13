/*
 * WaterBox.cpp
 *
 *  Created on: Jan 11, 2021
 *      Author: bit_creator
 */

#include "WaterBox.h"

using indexArray    = std::vector<glm::uvec3>;
using indexArrayPtr = std::unique_ptr<indexArray>;

WaterBox::WaterBox(float amplitude, float subdiv)
	: Geometry()
	, _amplitude(amplitude)
	, _subdiv(subdiv)
	, _vertices({
	 	 { glm::vec3( 1.,  1.,  1.), glm::vec3( 0.,  1.,  0.), glm::vec2(0.0f, 1.0f) },
		 { glm::vec3(-1.,  1.,  1.), glm::vec3( 0.,  1.,  0.), glm::vec2(0.0f, 1.0f) },
	     { glm::vec3(-1.,  1., -1.), glm::vec3( 0.,  1.,  0.), glm::vec2(0.0f, 0.0f) },
	     { glm::vec3( 1.,  1., -1.), glm::vec3( 0.,  1.,  0.), glm::vec2(1.0f, 0.0f) },
		 { glm::vec3( 0.,  1.,  0.), glm::vec3( 0.,  1.,  0.), glm::vec2(0.5f, 0.5f) }
	})
	, _indices(std::make_unique<std::vector<glm::uvec3>>(std::vector<glm::uvec3>{
    	glm::uvec3(4, 0, 1),
    	glm::uvec3(4, 1, 2),
	    glm::uvec3(4, 2, 3),
	    glm::uvec3(4, 3, 0)
	}))
{
	genSurface(_subdiv);
	recalculateUV();

	auto plateSize =  _vertices.size();

	_vertices.insert(
		_vertices.cend(), {
		{ glm::vec3( 1., -1.,  1.), glm::vec3( 0., -1.,  0.), glm::vec2(1, 1) },
		{ glm::vec3(-1., -1.,  1.), glm::vec3( 0., -1.,  0.), glm::vec2(0, 1) },
		{ glm::vec3(-1., -1., -1.), glm::vec3( 0., -1.,  0.), glm::vec2(0, 0) },
		{ glm::vec3( 1., -1., -1.), glm::vec3( 0., -1.,  0.), glm::vec2(1, 0) },

		{ glm::vec3( 1.,  1.,  1.), glm::vec3( 0.,  0.,  1.), glm::vec2(1, 1) },
		{ glm::vec3(-1.,  1.,  1.), glm::vec3( 0.,  0.,  1.), glm::vec2(0, 1) },
		{ glm::vec3(-1., -1.,  1.), glm::vec3( 0.,  0.,  1.), glm::vec2(0, 0) },
		{ glm::vec3( 1., -1.,  1.), glm::vec3( 0.,  0.,  1.), glm::vec2(1, 0) },

		{ glm::vec3(-1.,  1., -1.), glm::vec3( 0.,  0., -1.), glm::vec2(0, 1) },
		{ glm::vec3( 1.,  1., -1.), glm::vec3( 0.,  0., -1.), glm::vec2(1, 1) },
		{ glm::vec3( 1., -1., -1.), glm::vec3( 0.,  0., -1.), glm::vec2(1, 0) },
		{ glm::vec3(-1., -1., -1.), glm::vec3( 0.,  0., -1.), glm::vec2(0, 0) },

		{ glm::vec3(-1.,  1.,  1.), glm::vec3(-1.,  0.,  0.), glm::vec2(1, 1) },
		{ glm::vec3(-1.,  1., -1.), glm::vec3(-1.,  0.,  0.), glm::vec2(1, 0) },
		{ glm::vec3(-1., -1., -1.), glm::vec3(-1.,  0.,  0.), glm::vec2(0, 0) },
		{ glm::vec3(-1., -1.,  1.), glm::vec3(-1.,  0.,  0.), glm::vec2(0, 1) },

		{ glm::vec3( 1.,  1.,  1.), glm::vec3( 1.,  0.,  0.), glm::vec2(1, 1) },
		{ glm::vec3( 1.,  1., -1.), glm::vec3( 1.,  0.,  0.), glm::vec2(1, 0) },
		{ glm::vec3( 1., -1., -1.), glm::vec3( 1.,  0.,  0.), glm::vec2(0, 0) },
		{ glm::vec3( 1., -1.,  1.), glm::vec3( 1.,  0.,  0.), glm::vec2(0, 1) },
	});

	_indices->insert(
		_indices->cend(), {
	       glm::uvec3(plateSize, plateSize + 1, plateSize + 2),
	       glm::uvec3(plateSize, plateSize + 2, plateSize + 3),

	       glm::uvec3(plateSize + 4, plateSize + 5, plateSize + 6),
	       glm::uvec3(plateSize + 4, plateSize + 6, plateSize + 7),

	       glm::uvec3(plateSize + 8, plateSize + 9, plateSize + 10),
	       glm::uvec3(plateSize + 8, plateSize + 10, plateSize + 11),

	       glm::uvec3(plateSize + 12, plateSize + 13, plateSize + 14),
	       glm::uvec3(plateSize + 12, plateSize + 14, plateSize + 15),

	       glm::uvec3(plateSize + 16, plateSize + 17, plateSize + 18),
	       glm::uvec3(plateSize + 16, plateSize + 18, plateSize + 19)
	   });

	setNum(_indices->size() * 3,  _vertices.size());

	setupBuffers();
}

WaterBox::~WaterBox() noexcept {
}

void WaterBox::setupBuffers() noexcept {
    VAO.bind();
    VBO.bind();
    EBO.bind();

    VBO.loadData(_vertices, GL_STATIC_DRAW);
    EBO.loadData(*_indices, GL_STATIC_DRAW);

    VAO.addAttribute(Attribute::ATTRIB_POSITION, 8 * sizeof(GLfloat), 0);
    VAO.addAttribute(Attribute::ATTRIB_NORMAL, 8 * sizeof(GLfloat), 3 * sizeof(GLfloat));
//    VAO.addAttribute(Attribute::ATTRIB_TEX, 8 * sizeof(GLfloat), 6 * sizeof(GLfloat));


    VAO.enableAll();

    VBO.unbind();
    VAO.unbind();

}

void WaterBox::genSurface(GLuint sub) {
	if(--sub == 0) return;
	indexArrayPtr tmp = std::make_unique<indexArray>(indexArray(_indices->size() * 4, glm::uvec3()));
	GLint index = -1;
	for (const auto& triangle : *_indices) {
		auto res = divTriangle(triangle);
	    (*tmp)[++index] = res[0];
	    (*tmp)[++index] = res[1];
	    (*tmp)[++index] = res[2];
	    (*tmp)[++index] = res[3];
	}
	std::swap(_indices, tmp);
	genSurface(sub);
}

std::array<glm::uvec3, 4> WaterBox::divTriangle(glm::uvec3 triangle) {
	    auto point_1 = _vertices[triangle[0]]._coord;
	    auto point_2 = _vertices[triangle[1]]._coord;
	    auto point_3 = _vertices[triangle[2]]._coord;

	    auto point_1_2 = glm::vec3(
	        (point_1.x + point_2.x) / 2,
	        1,
	        (point_1.z + point_2.z) / 2
	    );

	    auto point_1_3 = glm::vec3(
	        (point_1.x + point_3.x) / 2,
	        1,
	        (point_1.z + point_3.z) / 2
	    );

	    auto point_2_3 = glm::vec3(
	        (point_2.x + point_3.x) / 2,
	        1,
	        (point_2.z + point_3.z) / 2
	    );

	    _vertices.push_back({ point_1_2, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) });
	    _vertices.push_back({ point_1_3, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) });
	    _vertices.push_back({ point_2_3, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) });

	    GLuint index_2_3 = _vertices.size() - 1;
	    GLuint index_1_3 = index_2_3 - 1;
	    GLuint index_1_2 = index_1_3 - 1;

	    return std::array<glm::uvec3, 4>({
	        glm::uvec3(triangle[0], index_1_2, index_1_3),
	        glm::uvec3(triangle[1], index_1_2, index_2_3),
	        glm::uvec3(triangle[2], index_1_3, index_2_3),
	        glm::uvec3(index_2_3, index_1_2, index_1_3)
	    });
}

void WaterBox::recalculateUV() {
	for (auto& vert : _vertices) {
		vert._texCoord.x = vert._coord.x * 0.5 + 0.5;
		vert._texCoord.y = vert._coord.z * 0.5 + 0.5;
	}
}
