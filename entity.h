/**
 * @file node.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef NODE_H
#define NODE_H

#include <list>
#include <vector>
#include <memory>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Transformation.h"

enum class EntityType
{
    CAMERA,
    OBJECT,
	LIGHT,
	NODE
};

class Entity {
public:
	/**
	 * proxy class for referencing to origin object placement in pool
	 * use offset in pools for geting address to object
	 */
	class reference {
	private:
		static constexpr inline size_t npos = std::numeric_limits<size_t>::max();

	private:
		size_t						_offset;
		EntityType					_type;

	public:
		reference();
		reference(size_t offset, EntityType type);

		auto operator <=>(const reference&) const =default;

		template < typename NodeT >
			NodeT* get();    // definition in "engine.h"

		void kill();
		bool expired() const;
		Entity* operator ->();
	};

protected:
// tree
	std::list < reference >		     						_childs;
	reference												_this;

	union {
		reference												_parent;
		reference												_next;
	};

//
    bool 													_enabled;
    const EntityType                                          _type;

public:
    Transformation											transform;


// creation
    Entity(EntityType type) noexcept;

// copy
    Entity(const Entity& oth) noexcept =delete;
    Entity& operator =(const Entity& oth) noexcept;
    reference copy(); 								// make a deep copy of subtree

// move
    Entity(Entity&&) noexcept =default;					// Need for pool construction "in place"
    Entity& operator=(Entity&&) noexcept = delete;

// destruction
    virtual ~Entity() noexcept =default;

// tree
    void addChild(reference child);
    void removeChild(reference child);

    std::list < reference >& getChilds();

	void unvalidateWorldMat() noexcept;
    glm::mat4 getWorldMat() noexcept;
	void update();

//
    EntityType getNodeType() const noexcept;

    void setEnabled(bool enabled);
    bool isEnabled();

	bool isDied() const;

	template < typename NodeT >
	friend class AbstractNodePool;
	friend class ObjectPool;
	friend class LightPool;
	friend class NodePool;
};


#endif // NODE_H
