/*
 * AbstractNodeRef.h
 *
 *  Created on: 7 черв. 2021 р.
 *      Author: iabernikhin
 */

#ifndef ABSTRACTNODEREF_H_
#define ABSTRACTNODEREF_H_

#include <limits>

using size_t = unsigned long long;

class Object3D;
class Light;
class Node;

class AbstractNodeRef {
protected:
	size_t			_offset ;
public:
	static inline size_t npos = std::numeric_limits<size_t>::max();

	AbstractNodeRef(size_t offset);
	virtual ~AbstractNodeRef();

	AbstractNodeRef& operator =(const AbstractNodeRef& oth);
	bool operator ==(const AbstractNodeRef& rhs);

	bool expired() const;

	virtual Node* get() const =0;
//	virtual size_t checkPos() const =0;
};

class ObjectRef : public AbstractNodeRef {
public:
	ObjectRef(size_t offset);
	virtual ~ObjectRef() override;

	Node* get() const override;
};

class LightRef : public AbstractNodeRef {
public:
	LightRef(size_t offset);
	virtual ~LightRef() override;

	Node* get() const override;
};

class NodeRef : public AbstractNodeRef {
public:
	NodeRef(size_t offset);
	virtual ~NodeRef() override;

	Node* get() const override;
};

class CameraRef : public AbstractNodeRef {
public:
	CameraRef();
	virtual ~CameraRef() override;

	Node* get() const override;
};


class NullRef : public AbstractNodeRef {
public:
	NullRef();
	virtual ~NullRef() override;

	Node* get() const override;
};
#endif /* ABSTRACTNODEREF_H_ */
