/*
 * NodePool.h
 *
 *  Created on: 3 черв. 2021 р.
 *      Author: IAbernikhin
 */

#ifndef ABSTRACTNODEPOOL_H_
#define ABSTRACTNODEPOOL_H_

#include <memory>
#include <vector>

#define DEBUG
#include "Macro.hpp"

class Node;
class Object3D;
class Light;

template < typename NodeT >
class AbstractNodePool {
	friend NodeT;

	std::vector < NodeT >								_pool;

	size_t												_maxId = 0;
	std::vector <size_t>								_freeId;

public:
	explicit AbstractNodePool(int reserv =30) {
		_pool.reserve(reserv);
	}

	AbstractNodePool(const AbstractNodePool& oth) =delete;
	AbstractNodePool& operator =(const AbstractNodePool& oth) =delete;

	~AbstractNodePool() {
		_pool.clear();
	}

	template< typename... Args >
//	std::shared_ptr < NodeT >
	size_t
	allocate(Args... args) {
		auto tmp = NodeT(std::forward<Args>(args)...);
		_pool.push_back(tmp);
//		auto ptr = std::shared_ptr<NodeT>(&_pool.back());

//		if(ptr == nullptr) ERROR("Node dont allocate");

		return _pool.size() - 1;
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

	NodeT* undegroundArray() {
		return &_pool[0];
	}
};

using ObjectPool = AbstractNodePool <Object3D>;
using LightPool = AbstractNodePool <Light>;
using NodePool  = AbstractNodePool <Node>;

#endif /* ABSTRACTNODEPOOL_H_ */
