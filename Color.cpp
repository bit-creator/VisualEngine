/*
 * Color.cpp
 *
 *  Created on: Dec 16, 2020
 *      Author: bit_creator
 */

#include "Color.h"

Color::Color()
	: _source(1.0, 1.0, 1.0, 1.0)
{  }

Color::Color(const glm::vec4 &color) {
	_source = color;
}

Color::Color(const glm::vec3 &color) {
	_source = glm::vec4(color, 1.0);
}

Color::Color(const float r, const float g, const float b, const float a) {
	_source = glm::vec4(r, g, b, a);
}

Color::Color(const float r, const float g, const float b) {
	_source = glm::vec4(r, g, b, 1.0);
}

Color::~Color() {
}

void Color::setColorSource(const glm::vec4 &color) {
	_source = color;
}

void Color::setColorSource(const glm::vec3 &color) {
	_source = glm::vec4(color, 1.0);
}

void Color::setColorSource(const float r, const float g, const float b,
		const float a) {
	_source = glm::vec4(r, g, b, a);
}

void Color::setColorSource(const float r, const float g, const float b) {
	_source = glm::vec4(r, g, b, 1.0);
}

void Color::setR(const float r) {
	_source.r = r;
}

void Color::setG(const float g) {
	_source.g = g;
}

void Color::setB(const float b) {
	_source.b = b;
}

void Color::setA(const float a) {
	_source.a = a;
}

glm::vec4 Color::getColorSource() const {
	return _source;
}

float Color::getR() const {
	return _source.r;
}

float Color::getG() const {
	return _source.g;
}

float Color::getB() const {
	return _source.b;
}

float Color::getA() const {
	return _source.a;
}
