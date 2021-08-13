/*
 * bindguard.h
 *
 *  Created on: 13 ρεπο. 2021 π.
 *      Author: IAbernikhin
 */

#ifndef GL_BINDGUARD_H_
#define GL_BINDGUARD_H_

#include <memory>

template < typename _Bindable >
class bind_guard {
private:
	using bind_type = _Bindable;
	using reference = bind_type&;

private:
	reference 			_object;

public:
	template < typename... Args >
	bind_guard(reference obj, Args&&... args)
	 : _object(obj)
	{
		_object.bind(std::forward<Args>(args)...);
	}

	~bind_guard() {
		_object.unbind();
	}

	bind_guard(const bind_guard&) = delete;
	bind_guard& operator=(const bind_guard&) = delete;
};

#endif /* GL_BINDGUARD_H_ */
