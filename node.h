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

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

enum class NodeType
{
    NODE_CAMERA,
    NODE_OBJECT
};

class Node
{
    protected:
        const NodeType                                          _type;
        glm::mat4                                               _modelMat;
        glm::quat                                               _rotate;
        glm::vec3                                               _position;
        glm::vec3                                               _scale;
        bool                                                    _dirtyTransform;

    public:
        Node(NodeType type) noexcept;

        void setRotate(const glm::vec3& axis, const GLfloat angle) noexcept;
        glm::quat getRotate() const noexcept;

        void setScale(const glm::vec3& scale) noexcept;
        glm::vec3 getScale() const noexcept;

        void setPosition(const glm::vec3& position) noexcept;
        glm::vec3 getPosition() const noexcept;

        glm::mat4 getModelMat() noexcept;
};

#endif // NODE_H
