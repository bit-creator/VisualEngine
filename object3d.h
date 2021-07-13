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

#include "entity.h"
#include "Geometry/geometry.h"
#include "Material/Material.h"

class Object3D final : public Entity {
public:
	using ID_t = std::uint8_t;
	static constexpr int maxID = std::numeric_limits<ID_t>::max();


private:
	GeometryPtr                                             _geom;
	MaterialPtr                                             _material;

	ID_t													_ID = 0;
	bool													_clicable =false;

protected:
	Object3D() noexcept;

    Object3D(const Object3D& oth) noexcept =delete;
    Object3D& operator=(Object3D&&) noexcept =delete;

// copy
    Object3D& operator =(const Object3D& oth) noexcept;

public:
	Object3D(Object3D&&) noexcept =default;					// Need for pool construction "in place"
    ~Object3D() noexcept =default;

    static reference
    create(MaterialPtr material =nullptr, GeometryPtr geometry =nullptr, bool clicable = false);

    Entity::reference copy() override;
	void destroy() override;


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

	template < typename NodeT >
	friend class AbstractNodePool;
	friend class ObjectPool;
};

#endif // OBJECT3D_H
