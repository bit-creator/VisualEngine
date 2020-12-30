/*
 * Color.h
 *
 *  Created on: Dec 16, 2020
*/

#ifndef COLOR_H_
#define COLOR_H_

#include <glm/glm.hpp>

class Color final {
private:
	glm::vec4						_source;

public:
	Color();
	~Color();

	Color(const Color &other) =default;
	Color(Color &&other) =default;

	Color& operator=(const Color &other) =default;
	Color& operator=(Color &&other) =default;

public:
	Color(const glm::vec4& color);
	Color(const glm::vec3& color);
	Color(const float r, const float g, const float b, const float a);
	Color(const float r, const float g, const float b);

	void setColorSource(const glm::vec4& color);
	void setColorSource(const glm::vec3& color);
	void setColorSource(const float r, const float g, const float b, const float a);
	void setColorSource(const float r, const float g, const float b);

	void setR(const float r);
	void setG(const float g);
	void setB(const float b);
	void setA(const float a);

	glm::vec4 getColorSource() const;

	float getR() const;
	float getG() const;
	float getB() const;
	float getA() const;
};

#endif /* COLOR_H_ */
