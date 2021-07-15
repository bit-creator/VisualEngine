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

#include "entity.h"
#include "Node.h"
#include "object3d.h"
#include "Light.h"

template < typename NodeT >
class AbstractNodePool {
	friend NodeT;

protected:
	std::vector < NodeT >									_pool;
	Entity::reference										_nextAvailable;
	float 													_maxLoadFactor;
	size_t													_alive;
	size_t													_pastTheLast;

public:
	virtual Entity::reference capture(Entity::reference) =0;
	virtual void release(Entity::reference) =0;

	explicit AbstractNodePool(int reserv =100)
		: _maxLoadFactor(0.7f)
		, _alive(0)
		,_pastTheLast(0)
	{
		_nextAvailable.kill();
		expand(reserv);
	}

	AbstractNodePool(const AbstractNodePool& oth) =delete;
	AbstractNodePool& operator =(const AbstractNodePool& oth) =delete;

	virtual ~AbstractNodePool() {
		clear();
	}

	float loadFactor() {
		return _alive / maxSize();
	}

	float fragmentationFactor() {
		return (float)_pastTheLast / _alive - 1;
		//(float)-^
	}

	void expand(int reserv) {
		_pool.reserve(reserv);
		auto startSize = _pool.size();
		for(int ind = 0; ind < reserv; ++ind) {
			_pool.emplace_back(std::move(NodeT()));
			if(ind == 0) {
				if(startSize == 0) {
					_nextAvailable = Entity::reference(0, getType());
				} else {
					auto ref = _nextAvailable;
					while(!ref->_next.expired()) ref = ref->_next;
					ref->_next = Entity::reference(startSize, getType());
				}
			} else {
				_pool[startSize + ind - 1]._next = Entity::reference(ind + startSize, getType());
			}
		}
		_pool[startSize + reserv - 1]._next.kill();
	}

	void remap(int new_size) {
		clear();
		expand(new_size);
	}

	auto begin()   { return _pool.begin();   }
	auto cbegin()  { return _pool.cbegin();  }
	auto rbegin()  { return _pool.rbegin();  }
	auto crbegin() { return _pool.crbegin(); }

//	auto end()     { return _pool.end(); }
//	auto cend()    { return _pool.cend(); }
//	auto rend()    { return _pool.rend(); }
//	auto crend()   { return _pool.crend(); }

	auto end()     { return begin() + _pastTheLast; }
	auto cend()    { return cbegin() + _pastTheLast; }
	auto rend()    { return rbegin() + _pastTheLast; }
	auto crend()   { return crbegin() + _pastTheLast; }

	auto maxSize() { return _pool.size(); }
	auto alive()   { return _alive; }


	void clear() {_pool.clear(); }

	auto& operator [](size_t ind) const {
		return _pool[ind];
	}

	NodeT* undegroundArray() {
		return &_pool[0];
	}

protected:
	Entity::reference captureImpl(Entity::reference parent) {
		Entity::reference ref = _nextAvailable;

		if(ref.expired()) {
			MESSAGE("doesnt allocate pull is full");
			return ref;
		}

		if(!ref->isDied()) {
			MESSAGE("captured object now alive");
			return ref;
		}

		if((size_t)ref == _pastTheLast) ++_pastTheLast;

		_nextAvailable = ref->_next;
		ref->_parent = Entity::reference();
		ref->_this = ref;

		parent->addChild(ref);

		++_alive;

		return ref;
	}

	void releaseImpl(Entity::reference ref) {
		if(ref.expired()) {
			MESSAGE("expired reference not deleted");
			return;
		}

		if(ref->isDied()) {
			MESSAGE("reference alredy released");
			return;
		}

//		ref->_parent->removeChild(ref);

		ref->_this.kill();

		if((size_t)ref == _pastTheLast - 1) --_pastTheLast;

		ref->_next = _nextAvailable;
		_nextAvailable = ref;

		--_alive;
	}

private:
	inline constexpr EntityType getType() {
		if constexpr (std::same_as<NodeT, Object3D>) return EntityType::OBJECT;
		if constexpr (std::same_as<NodeT, Light>) 	 return EntityType::LIGHT;
		if constexpr (std::same_as<NodeT, Node>) 	 return EntityType::NODE;
		return EntityType::NODE;
	}
};

class ObjectPool : public AbstractNodePool <Object3D> {
	friend Object3D;
private:
	size_t												_maxId = 0;
	std::vector <size_t>								_freeId;

public:
	explicit ObjectPool(int reserv);

	Entity::reference capture(Entity::reference parent);
	void release(Entity::reference ref);

	size_t getMaxId();
};

class LightPool : public AbstractNodePool <Light> {
private:
	size_t							_num;

public:
	explicit LightPool(int reserv);

	Entity::reference capture(Entity::reference parent);
	void release(Entity::reference ref);

	size_t capacity();
};

class NodePool : public AbstractNodePool <Node> {
public:
	explicit NodePool(int reserv);

	Entity::reference capture(Entity::reference parent);
	void release(Entity::reference ref);
};

#endif /* ABSTRACTNODEPOOL_H_ */
