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

#include "CreateAsPointer.hpp"
#include "Ray.h"
#include "AbstractNodeRef.h"


enum class NodeType
{
    NODE_CAMERA,
    NODE_OBJECT,
	NODE_LIGHT,
	NODE_NODE
};

class Node : public std::enable_shared_from_this < Node > {
public:
	class reference {
	private:
		AbstractNodeRef*					_ref;

	public:
		reference() : _ref(new NullRef()) {  }

		reference& operator =(const AbstractNodeRef& oth) {
			if (this->_ref == &oth) return *this;
			*_ref = oth;
			return *this;
		}

		reference(AbstractNodeRef* ref) : _ref(ref) {  }

		auto operator <=>(const reference&) const =default;

		Node* get() {
			return _ref->get();
		}

		bool expired() {
			return _ref->expired();
		}

		Node* operator ->() {
			return _ref->get();
		}
	};

//	using reference = std::shared_ptr < Node >;

protected:
	std::list < reference >		     						_childs;
//	std::weak_ptr < Node >									_parent;
	reference												_parent;
	reference												_this;

    const NodeType                                          _type;
    glm::mat4                                               _modelMat;
    glm::mat4												_worldMat;
    glm::quat                                               _rotate;
    glm::vec3                                               _position;
    glm::vec3                                               _scale;
    bool                                                    _dirtyTransform;
    bool 													_dirtyWorldTransform;
    bool 													_enabled;

public:
	Node() noexcept;
    Node(NodeType type) noexcept;
    Node(const Node& oth) noexcept;
    Node(Node&&) noexcept = delete;
    virtual ~Node() noexcept;

    static reference create(NodeType type =NodeType::NODE_NODE);

    NodeType getNodeType() const noexcept;

    void setRotate(const glm::vec3& axis, const float angle) noexcept;
    void setRotate(const glm::vec3& angles) noexcept;

    glm::quat getRotate() const noexcept;

    void setScale(const glm::vec3& scale) noexcept;
    glm::vec3 getScale() const noexcept;

    void setPosition(const glm::vec3& position) noexcept;
    glm::vec3 getPosition() const noexcept;

    glm::mat4 getModelMat() noexcept;
    glm::mat4 getWorldMat() noexcept;

    void setEnabled(bool enabled);
    bool isEnabled();

public: 		// CHILD
	void addChild(reference child);
    void removeChild(reference child);

    reference referenceFromThis() const;

    std::list < reference >&
    getChilds();

    std::list < Intersection >
    rayCast(Ray ray);

    virtual Object3D* search(int id);

	void unvalidateWorldMat() noexcept;

protected:
	virtual void rayCastImpl(Ray& ray, std::list < Intersection >& list);
};

using NodePtr = Node::reference;

#endif // NODE_H
