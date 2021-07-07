/**
 * @file Object3D.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <memory>
#include <limits>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "node.h"
#include "Geometry/geometry.h"
#include "camera.h"
#include "CreateAsPointer.hpp"

#include "GL/buffer.h"
#include "GL/vertexarray.h"
#include "GL/shaderprogram.h"
#include "Material/Material.h"

class Object3D final : public Node {
public:
	using ID_t = std::uint8_t;
	static constexpr int maxID = std::numeric_limits<ID_t>::max();
	friend class ObjectPool;
private:
	GeometryPtr                                             _geom;
	ID_t													_ID = 0;
	bool													_clicable =false;

protected:          //  Material
	MaterialPtr                                             _material;

public:
	Object3D() noexcept;
    Object3D(const Object3D& oth) noexcept;
    Object3D(MaterialPtr material) noexcept;
    Object3D(MaterialPtr material, GeometryPtr geometry) noexcept;

public:
    virtual ~Object3D() noexcept;

    static reference
    create(MaterialPtr material =nullptr, GeometryPtr geometry =nullptr);

    void setGeometry(GeometryPtr geometry) noexcept;
    GeometryPtr getGeometry() const noexcept;

    void setMaterial(MaterialPtr material) noexcept;
    MaterialPtr getMaterial() const noexcept;

	size_t getID() const;

	glm::vec4 getColorKey() const;

	void setClicable(bool clicable);
	bool isClicable() const;

	inline constexpr static GLenum getColorKeyFormat() {
		if constexpr (sizeof(Object3D::ID_t) == 1) return GL_RED;
		if constexpr (sizeof(Object3D::ID_t) == 2) return GL_RG;
		if constexpr (sizeof(Object3D::ID_t) == 3) return GL_RGB;
		if constexpr (sizeof(Object3D::ID_t) == 4) return GL_RGBA;
	}

private:
	void resetID();
};

#endif // OBJECT3D_H
