/*
 * Crystal.cpp
 *
 *  Created on: Jan 18, 2021
 *      Author: bit_creator
 */

#include "Crystal.h"
#include <glm/gtx/normal.hpp>
#include <glm/gtx/string_cast.hpp>

Crystal::Crystal(FacetingType type, GLuint angles) noexcept
	: _type(type)
	, _angles(angles)
{ genSimple(); setNum(_indices.size() * 3,  _vertices.size()); setupBuffers();  }

Crystal::~Crystal() noexcept {
}

void Crystal::genSimple() {
	const float height = 2.0f / 3.0f;
	const float alpha = M_PI / 3.0f;

	float radDif = 1.0 - height * (cos(alpha) / sin(alpha));

	genFigure(radDif);

	auto figurSize = _indices.size();

	for (GLuint i = 0; i < figurSize; i++) {
		auto triangle = _indices[i];
		glm::vec3 point_1(_vertices[triangle[1]]._pos.x, 1, _vertices[triangle[1]]._pos.z);
		glm::vec3 point_2(_vertices[triangle[2]]._pos.x, 1, _vertices[triangle[2]]._pos.z);

		glm::vec3 point_3(_vertices[triangle[1]]._pos.x * (1 / radDif), height, _vertices[triangle[1]]._pos.z * (1 / radDif));
		glm::vec3 point_4(_vertices[triangle[2]]._pos.x * (1 / radDif), height, _vertices[triangle[2]]._pos.z * (1 / radDif));

		glm::vec3 point_5(0.0f, -1.0f, 0.0f);

		auto faceNormal = glm::triangleNormal(point_1, point_2, point_3);
		auto trNormal = glm::triangleNormal(point_3, point_4, point_5);

		auto pos = _vertices.size();

		_vertices.push_back({ point_1, faceNormal });
		_vertices.push_back({ point_2, faceNormal });
		_vertices.push_back({ point_3, faceNormal });
		_vertices.push_back({ point_4, faceNormal });
		_vertices.push_back({ point_3, trNormal });
		_vertices.push_back({ point_4, trNormal });
		_vertices.push_back({ point_5, trNormal });

		_indices.push_back({ pos, pos + 1, pos + 2 });
		_indices.push_back({ pos + 1, pos + 2, pos + 3 });
		_indices.push_back({ pos + 4, pos + 5, pos + 6 });
	}

//	for (auto tr : _indices) {
//		std::cout << glm::to_string(tr) << std::endl;
//	}
//	for (auto vert : _vertices) {
//		std::cout << glm::to_string(vert._pos) << std::endl;
//	}
//	for (auto vert : _vertices) {
//		std::cout << glm::to_string(vert._normal) << std::endl;
//	}
}

void Crystal::genFigure(const float rad) {
	auto firstInd = _vertices.size();

	_vertices.push_back({ glm::vec3(0, 1, 0), glm::vec3(0, 1, 0) });
	_vertices.push_back({ glm::vec3(rad, 1, 0), glm::vec3(0, 1, 0) });

	auto angle = (2 * M_PI) / _angles;

	for (GLuint i = 1; i < _angles; ++i) {
		auto currentAngle = i * angle;
		_vertices.push_back({ glm::vec3(rad * cos(currentAngle), 1, rad * sin(currentAngle)), glm::vec3(0, 1, 0) });
		_indices.push_back( glm::uvec3(firstInd, i, i + 1) );
	}
	_indices.push_back({ firstInd, firstInd + 1, _angles });
}

void Crystal::setupBuffers() noexcept
{
    VAO.bind();
    VBO.bind();
    EBO.bind();

    VBO.loadData(_vertices, GL_STATIC_DRAW);
    EBO.loadData(_indices, GL_STATIC_DRAW);

    VAO.addAttribute(Attribute::ATTRIB_POSITION, 6 * sizeof(GLfloat), 0);
    VAO.addAttribute(Attribute::ATTRIB_NORMAL, 6 * sizeof(GLfloat), 3);

    VAO.enableAll();

    VBO.unbind();
    VAO.unbind();
}
