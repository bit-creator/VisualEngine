/*
 * Ray.h
 *
 *  Created on: Jan 13, 2021
 *      Author: bit_creator
 */

#ifndef RAY_H_
#define RAY_H_

#include <memory>

#include <glm/glm.hpp>

//#include "object3d.h"

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

/*
 * Intersection {
 *		 distance – distance between the origin of the ray and the intersection
 * 		 point – point of intersection, in world coordinates
 * 		 object – the intersected object
 * }
 */
class Object3D;

struct Intersection {
	const float 										_distance;
	const glm::vec3										_point;
	Object3D*											_obj;
};


#endif /* RAY_H_ */
