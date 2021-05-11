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

class Object3D final :
	public Node,
	public MultiSharedCreator < Object3D, Node > {
public:
	using ID_t = std::uint8_t;
	static constexpr int maxID = std::numeric_limits<ID_t>::max();

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

    virtual ~Object3D() noexcept;

    void setGeometry(GeometryPtr geometry) noexcept;
    GeometryPtr getGeometry() const noexcept;

    void setMaterial(MaterialPtr material) noexcept;
    MaterialPtr getMaterial() const noexcept;

public:
	void rayCastImpl(Ray& ray, std::list < Intersection >& list) override;
	Object3D* search(int id) override;

	glm::vec4 getColorKey() const;
	ID_t getID() const;
	void setID(ID_t id);

	void setClicable(bool clicable);
	bool isClicable() const;
	void resetID();


	inline constexpr static GLenum getColorKeyFormat() {
		if constexpr (sizeof(Object3D::ID_t) == 1) return GL_RED;
		if constexpr (sizeof(Object3D::ID_t) == 2) return GL_RG;
		if constexpr (sizeof(Object3D::ID_t) == 3) return GL_RGB;
		if constexpr (sizeof(Object3D::ID_t) == 4) return GL_RGBA;
	}
};

using ObjPtr = std::shared_ptr < Object3D >;

#endif // OBJECT3D_H
