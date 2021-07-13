/*
 * Node.cpp
 *
 *  Created on: 7 ���. 2021 �.
 *      Author: IAbernikhin
 */

#include "Node.h"
#include "engine.h"

Node::Node() noexcept
	: Entity(EntityType::NODE)
{  }

Node::reference Node::create() {
	return Engine::engine().getScene()->nodes.capture();
}

Node& Node::operator =(const Node &oth) noexcept {
}

Node::reference Node::copy() {
}

void Node::destroy() {
}
