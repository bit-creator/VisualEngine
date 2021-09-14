/*
 * RowGraphicObject.h
 *
 *  Created on: 14 вер. 2021 р.
 *      Author: IAbernikhin
 */

#ifndef GL_ROWGRAPHICOBJECT_H_
#define GL_ROWGRAPHICOBJECT_H_

#include <concepts>
#include <functional>
#include <limits>

#include "../Macro.hpp"

#include "Creators.h"
#include "Deleters.h"

using ObjIdT = uint32_t;

template <
	auto Creator,
	auto Deleter
> class RowGraphicObject {
protected:
	ObjIdT				_object =std::numeric_limits<ObjIdT>::max();;

protected:
	RowGraphicObject() requires
			std::invocable<decltype(Creator), ObjIdT*> {
				std::invoke(Creator, &_object);
		}

	template < typename... Args >
	RowGraphicObject(Args... args) requires
		std::invocable<decltype(Creator), ObjIdT*, Args...> {
			std::invoke(Creator, &_object, std::forward<Args...>(args...));
	}

	~RowGraphicObject() requires
		std::invocable<decltype(Deleter), ObjIdT*> {
			std::invoke(Deleter, &_object);
	}

	RowGraphicObject& operator=(const RowGraphicObject& oth) {
		if( this == &oth ) return *this;
		WARNING("COPY OF ROW GRAPHIC OBJECT");
		std::invoke(Deleter, &_object);
		std::invoke(Creator, &_object);
		return *this;
	}

	RowGraphicObject& operator=(RowGraphicObject&& oth) {
		if( this == &oth ) return *this;
		WARNING("COPY OF ROW GRAPHIC OBJECT");
		std::invoke(Deleter, &_object);
		std::invoke(Creator, &_object);
		return *this;
	}
	RowGraphicObject(const RowGraphicObject& oth) requires
			std::invocable<decltype(Creator), ObjIdT*> {
		std::invoke(Creator, &_object);
	}
	RowGraphicObject(RowGraphicObject&& oth) requires
			std::invocable<decltype(Creator), ObjIdT*> {
		std::invoke(Creator, &_object);
	}
public:
	ObjIdT getID() const { return _object; }
};

#ifdef USE_GL
	using namespace GL;
#endif // USE_GL

#endif /* GL_ROWGRAPHICOBJECT_H_ */
