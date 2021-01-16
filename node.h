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

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Ray.h"

enum class NodeType
{
    NODE_CAMERA,
    NODE_OBJECT,
	NODE_LIGHT,
	NODE_NODE
};

class Node
		: public std::enable_shared_from_this < Node >
{
    protected:
		std::list < std::shared_ptr < Node > >		     		_childs;
		std::weak_ptr < Node >									_parent;

        const NodeType                                          _type;
        glm::mat4                                               _modelMat;
        glm::mat4												_worldMat;
        glm::quat                                               _rotate;
        glm::vec3                                               _position;
        glm::vec3                                               _scale;
        bool                                                    _dirtyTransform;
        bool 													_dirtyWorldTransform;

    public:
        Node(NodeType type) noexcept;
        Node(const Node& oth) noexcept;
        Node(Node&&) noexcept = delete;

        NodeType getNodeType() const noexcept;

        void setRotate(const glm::vec3& axis, const GLfloat angle) noexcept;
        void setRotate(const glm::vec3& angles) noexcept;

        glm::quat getRotate() const noexcept;

        void setScale(const glm::vec3& scale) noexcept;
        glm::vec3 getScale() const noexcept;

        void setPosition(const glm::vec3& position) noexcept;
        glm::vec3 getPosition() const noexcept;

        glm::mat4 getModelMat() noexcept;
        glm::mat4 getWorldMat() noexcept;

    public: 		// CHILD
        void addChild(std::shared_ptr < Node > child);
        void removeChild(std::shared_ptr < Node > child);

        std::list < std::shared_ptr < Node > >&
        getChilds();

        std::list < std::shared_ptr < Node > >
        rayCast(Ray ray);

		void unvalidateWorldMat() noexcept;

    private:
		std::vector<Intersection> rayCastGeom(Ray ray);
		void rayCastImpl(Ray ray, std::list < std::shared_ptr < Node > >& list);
};

using NodePtr = std::shared_ptr < Node >;

#endif // NODE_H
