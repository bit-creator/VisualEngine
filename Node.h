/*
 * Node.h
 *
 *  Created on: 7 лип. 2021 р.
 *      Author: IAbernikhin
 */

#ifndef NODE_H_
#define NODE_H_

#include "entity.h"

class Node : public Entity {
public:
// creation
	Node() noexcept;
    void initialize();
    static reference create();

// copy
//    Node(const Node& oth) noexcept;
    Entity& operator =(const Node& oth) noexcept;
    reference copy();

// move
    Node(Node&&) noexcept =default;
    Node& operator=(Node&&) noexcept = delete;

// destruction
    virtual ~Node() noexcept;
    void deinitialize();
};

#endif /* NODE_H_ */
