/*
 * NodePool.h
 *
 *  Created on: 3 черв. 2021 р.
 *      Author: IAbernikhin
 */

#ifndef NODEPOOL_H_
#define NODEPOOL_H_

#include <memory>
#include <vector>

#define DEBUG
#include "Macro.hpp"

class Node;
class Object3D;
class Light;

template < typename NodeT >
class NodePool {
	friend NodeT;

	std::vector < NodeT >								_pool;

	size_t												_maxId = 0;
	std::vector <size_t>								_freeId;

public:
	explicit NodePool(int reserv =30) {
		_pool.reserve(reserv);
	}

	NodePool(const NodePool& oth) =delete;
	NodePool& operator =(const NodePool& oth) =delete;

	~NodePool() {
		_pool.clear();
	}

	template< typename... Args >
	std::shared_ptr < NodeT >
	allocate(Args... args) {
		auto tmp = NodeT(std::forward<Args>(args)...);
		_pool.push_back(tmp);
		auto ptr = std::shared_ptr<NodeT>(&_pool.back());

		if(ptr == nullptr) ERROR("Node dont allocate");

		return ptr;
	}

	void clear() {
		_pool.clear();
	}

	void remove(std::shared_ptr < Node > obj) {
		_pool.remove(obj);
	}

	void reserve(int res) {
//		_pool.reserve(res);
	}

	auto begin() {
		return _pool.begin();
	}

	auto end() {
		return _pool.end();
	}

	size_t size() {
		return _pool.size();
	}

	size_t getMaxId() {
		return _maxId;
	}


};

using ObjectPool = NodePool <Object3D>;
using LightPool = NodePool <Light>;


#endif /* NODEPOOL_H_ */
