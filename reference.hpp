/*
 * reference.hpp
 *
 *  Created on: 5 ���. 2021 �.
 *      Author: iabernikhin
 */

#ifndef REFERENCE_HPP_
#define REFERENCE_HPP_

#include "engine.h"

template<typename NodeT>
inline NodeT* Node::reference::get() {
	return Engine::engine().getPool<NodeT>() + _offset;
}




#endif /* REFERENCE_HPP_ */
