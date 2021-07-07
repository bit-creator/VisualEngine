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

enum class NodeType
{
    NODE_CAMERA,
    NODE_OBJECT,
	NODE_LIGHT,
	NODE_NODE
};

class Node {
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
		NodeType					_type;

	public:
		reference();
		reference(size_t offset, NodeType type);

		auto operator <=>(const reference&) const =default;

		template < typename NodeT >
			NodeT* get();    // definition in "engine.h"

		void kill();
		bool expired() const;
		Node* operator ->();
	};

protected:
// tree
	std::list < reference >		     						_childs;
	reference												_this;

	union {
		reference												_parent;
		reference												_next;
	};

// transformation
    glm::mat4                                               _modelMat;
    glm::mat4												_worldMat;
    glm::quat                                               _rotate;
    glm::vec3                                               _position;
    glm::vec3                                               _scale;
    bool                                                    _dirtyTransform;
    bool 													_dirtyWorldTransform;

//
    bool 													_enabled;
    const NodeType                                          _type;

public:
// creation
	Node() noexcept;								// default constructor, need for pool
    Node(NodeType type) noexcept;
    void initialize();								// move to interface make pure virtual
    static reference create();						// capture object from pool and initialize his

// copy
    Node(const Node& oth) noexcept; 				// this use?
    Node& operator =(const Node& oth) noexcept;
    reference copy(); 								// make a deep copy of subtree

// move
    Node(Node&&) noexcept =default;					// Need for pool construction "in place"
    Node& operator=(Node&&) noexcept = delete;

// destruction
    virtual ~Node() noexcept;
    void deinitialize();							// move to interface make pure virtual

// tree
    void addChild(reference child);
    void removeChild(reference child);

    std::list < reference >& getChilds();

	void unvalidateWorldMat() noexcept;

// transformation
    void setRotate(const glm::vec3& axis, const float angle) noexcept;
    void setRotate(const glm::vec3& angles) noexcept;
    glm::quat getRotate() const noexcept;

    void setScale(const glm::vec3& scale) noexcept;
    glm::vec3 getScale() const noexcept;

    void setPosition(const glm::vec3& position) noexcept;
    glm::vec3 getPosition() const noexcept;

    glm::mat4 getModelMat() noexcept;
    glm::mat4 getWorldMat() noexcept;

//
    NodeType getNodeType() const noexcept;

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
