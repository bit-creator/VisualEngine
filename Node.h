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
protected:
	Node() noexcept;

	Node(const Node& oth) noexcept =delete;
	Node& operator=(Node&&) noexcept = delete;

// copy
	Node& operator =(const Node& oth) noexcept;

public:
	Node(Node&&) noexcept =default;					// Need for pool construction "in place"
    ~Node() noexcept =default;

    static reference
    create();

    Entity::reference copy() override;
	void destroy() override;

	template < typename NodeT >
	friend class AbstractNodePool;
	friend class NodePool;
};

#endif /* NODE_H_ */
