/*
 * Node.cpp
 *
 *  Created on: 7 лип. 2021 р.
 *      Author: IAbernikhin
 */

#include "Node.h"
#include "engine.h"

Node::Node() noexcept
	: Entity(EntityType::NODE)
{  }

void Node::initialize() {
}

Node::reference Node::create() {
	return Engine::engine().getScene()->nodes.capture();
}

//Node::Node(const Node &oth) noexcept
//	: Entity(oth)
//{  }

Entity& Node::operator =(const Node &oth) noexcept {
}

Node::reference Node::copy() {
}

Node::~Node() noexcept {
}

void Node::deinitialize() {
}
