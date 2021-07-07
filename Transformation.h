/*
 * Transformation.h
 *
 *  Created on: 7 лип. 2021 р.
 *      Author: IAbernikhin
 */

#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Transformation {
private:
    glm::mat4                                               _modelMat;
    glm::mat4												_worldMat;
    glm::quat                                               _rotate;
    glm::vec3                                               _position;
    glm::vec3                                               _scale;
    bool                                                    _dirtyTransform;
    bool 													_dirtyWorldTransform;

public:
	Transformation();
	Transformation(const Transformation&) =delete;
	Transformation& operator=(const Transformation&) =delete;
	Transformation(Transformation&&) =default;
	Transformation& operator=(Transformation&&) =delete;
	~Transformation() =default;

    void setRotate(const glm::vec3& axis, const float angle) noexcept;
    void setRotate(const glm::vec3& angles) noexcept;
    glm::quat getRotate() const noexcept;

    void setScale(const glm::vec3& scale) noexcept;
    glm::vec3 getScale() const noexcept;

    void setPosition(const glm::vec3& position) noexcept;
    glm::vec3 getPosition() const noexcept;

    glm::mat4 getModelMat() noexcept;

    friend class Entity;
};

#endif /* TRANSFORMATION_H_ */
