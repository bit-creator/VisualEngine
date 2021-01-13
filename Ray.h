/*
 * Ray.h
 *
 *  Created on: Jan 13, 2021
 *      Author: bit_creator
 */

#ifndef RAY_H_
#define RAY_H_

#include <glm/glm.hpp>

class Ray final {
private:
	glm::vec3										_direction;
	glm::vec3										_origin;
public:
	Ray();
	Ray(const glm::vec3 direction, const glm::vec3 origin);
	~Ray();

	void setRay(glm::vec3 direction, glm::vec3 origin);
	void setDirection(glm::vec3 direction);
	void setOrigin(glm::vec3 origin);

	const glm::vec3 getDirection() const;
	const glm::vec3 getOrigin() const;
};

#endif /* RAY_H_ */
