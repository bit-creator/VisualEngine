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

#include "node.h"
#include "object3d.h"
#include "Light.h"

template < typename NodeT >
class AbstractNodePool {
	friend NodeT;

protected:
	std::vector < NodeT >								_pool;
	Node::reference										_nextAvailable;

public:
	virtual Node::reference capture(void) =0;
	virtual void release(Node::reference) =0;

	explicit AbstractNodePool(int reserv =30) {
		_nextAvailable.kill();
		expand(reserv);
	}

	AbstractNodePool(const AbstractNodePool& oth) =delete;
	AbstractNodePool& operator =(const AbstractNodePool& oth) =delete;

	virtual ~AbstractNodePool() {
		clear();
	}

	void expand(int reserv) {
		_pool.reserve(reserv);
		auto startSize = _pool.size();
		for(int ind = 0; ind < reserv; ++ind) {
			_pool.emplace_back(std::move(NodeT()));
			if(ind == 0) {
				if(startSize == 0) {
					_nextAvailable = Node::reference(0, getType());
				} else {
					auto ref = _nextAvailable;
					while(!ref->_next.expired()) ref = ref->_next;
					ref->_next = Node::reference(startSize, getType());
				}
			} else {
				_pool[startSize + ind - 1]._next = Node::reference(ind + startSize, getType());
			}
		}
		_pool[startSize + reserv - 1]._next.kill();
	}

	void remap(int new_size) {
		clear();
		expand(new_size);
	}

	auto begin()   { return _pool.begin();   }
	auto end()     { return _pool.end();     }
	auto cbegin()  { return _pool.cbegin();  }
	auto cend()    { return _pool.cend();    }
	auto rbegin()  { return _pool.rbegin();  }
	auto rend()    { return _pool.rend();    }
	auto crbegin() { return _pool.crbegin(); }
	auto crend()   { return _pool.crend();   }
	auto size()    { return _pool.size();    }

	void clear() {_pool.clear(); }

	auto& operator [](size_t ind) const {
		return _pool[ind];
	}

	NodeT* undegroundArray() {
		return &_pool[0];
	}

private:
	inline constexpr NodeType getType() {
		if constexpr (std::same_as<NodeT, Object3D>) return NodeType::NODE_OBJECT;
		if constexpr (std::same_as<NodeT, Light>) 	 return NodeType::NODE_LIGHT;
		if constexpr (std::same_as<NodeT, Node>) 	 return NodeType::NODE_NODE;
		return NodeType::NODE_NODE;
	}
};

class ObjectPool : public AbstractNodePool <Object3D> {
	friend Object3D;
private:
	size_t												_maxId = 0;
	std::vector <size_t>								_freeId;

public:
	explicit ObjectPool(int reserv) : AbstractNodePool(reserv) {  }

	Node::reference capture(void) {
		auto obj = _nextAvailable;
		if(!obj->isDied()) {
			MESSAGE("something very bad");
		}

		_nextAvailable = obj->_next;
		obj->_parent = Node::reference();
		obj->_this = obj;

		return obj;
	}

	void release(Node::reference ref) {
		if(ref.expired()) {
			MESSAGE("something very bad");
		}

		if(ref->isDied()) return;

		// deinitialise


		ref->_next = _nextAvailable;
		_nextAvailable = ref;
	}

	size_t getMaxId() {
		return _maxId;
	}
};

class LightPool : public AbstractNodePool <Light> {
private:
	size_t							_num;

public:
	explicit LightPool(int reserv)
		: AbstractNodePool(reserv)
		, _num(0)
	{  }

	Node::reference capture(void) {
		auto obj = _nextAvailable;
		if(!obj->isDied()) {
			MESSAGE("something very bad");
		}

		_nextAvailable = obj->_next;
		obj->_parent = Node::reference();
		obj->_this = obj;

		++_num;

		return obj;
	}

	void release(Node::reference ref) {
		if(ref.expired()) {
			MESSAGE("something very bad");
		}

		if(ref->isDied()) return;

		// deinitialise


		--_num;

		ref->_next = _nextAvailable;
		_nextAvailable = ref;
	}

	size_t capacity() {
		return _num;
	}
};

class NodePool : public AbstractNodePool <Node> {
public:
	explicit NodePool(int reserv) : AbstractNodePool(reserv) {
		_pool[0]._this = Node::reference(0, NodeType::NODE_NODE);
		_pool[0]._parent = Node::reference();

		_nextAvailable = Node::reference(1, NodeType::NODE_NODE);
	}

	Node::reference capture(void) {

//		MESSAGE(_pool.size());

		auto ref = _nextAvailable;

		auto obj = ref.get<Node>();
		if(!obj->isDied()) {
			MESSAGE("something very bad");
		}

		_nextAvailable = obj->_next;
		obj->_parent = Node::reference();
		obj->_this = ref;

		return ref;
	}

	void release(Node::reference ref) {
		if(ref.expired()) {
			MESSAGE("something very bad");
		}

		if(ref->isDied()) return;

		// deinitialise


		ref->_next = _nextAvailable;
		_nextAvailable = ref;
	}
};


//using ObjectPool = AbstractNodePool <Object3D>;
//using LightPool = AbstractNodePool <Light>;
//using NodePool  = AbstractNodePool <Node>;

#endif /* ABSTRACTNODEPOOL_H_ */
