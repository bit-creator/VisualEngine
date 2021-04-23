/*
 * lifecicle.hpp
 *
 *  Created on: 20 квіт. 2021 р.
 *      Author: IAbernikhin
 */

#ifndef CREATEASPOINTER_HPP_
#define CREATEASPOINTER_HPP_

#include <memory>

template <
	template < typename... >
		typename _Ptr,
	typename _Tp,
	typename _Base
> struct PointerSpec {
	using pointerToBase = _Ptr < _Base >;
	using pointer = _Ptr < _Tp >;
};

template <
	template < typename... >
		typename _Ptr,
	typename _Tp,
	typename _Base,
	typename _Deleter
> struct Creator : private PointerSpec < _Ptr, _Tp, _Base > {
	using Spec = PointerSpec < _Ptr, _Tp, _Base >;
	using typename Spec::pointerToBase;
	using typename Spec::pointer;
	template < typename... Args > pointerToBase
	static inline createImpl(Args&&... args) {
		return pointer(new _Tp(std::forward<Args>(args)...)
			,_Deleter()
		);
	}
};

template <
	typename _Tp,
	typename _Base = _Tp,
	typename _Deleter = std::default_delete<_Tp>
> struct SharedCreator : private
	Creator< std::shared_ptr, _Tp, _Base, _Deleter > {
	using Creator = Creator < std::shared_ptr, _Tp, _Base, _Deleter >;
	using Creator::createImpl;
	template < typename... Args > auto
	static inline create(Args&&... args) {
		return createImpl(std::forward<Args>(args)...);
	}
};

template <
	typename _Tp,
	typename _Base = _Tp,
	typename _Deleter = std::default_delete<_Tp>
> struct UniqueCreator : private
	Creator < std::unique_ptr, _Tp, _Base, _Deleter > {
	using Creator = Creator < std::unique_ptr, _Tp, _Base, _Deleter >;
	using Creator::createImpl;
	template < typename... Args > auto
	static inline create(Args&&... args) {
		return createImpl(std::forward<Args>(args)...);
	}
};

template <
	typename _Tp,
	typename _Base,
	typename _Deleter = std::default_delete<_Tp>
> struct CreatAsSharedToBase : private
	SharedCreator < _Tp, _Base, _Deleter > {
	using SharedCreator = SharedCreator < _Tp, _Base, _Deleter >;
	using SharedCreator::create;
	template < typename... Args > auto
	static inline createSharedBasePtr(Args&&... args) {
		return create(std::forward<Args>(args)...);
	}
};

template <
	typename _Tp,
	typename _Deleter = std::default_delete<_Tp>
> struct CreatAsShared : private
	SharedCreator < _Tp, _Tp, _Deleter > {
	using SharedCreator = SharedCreator < _Tp, _Tp, _Deleter >;
	using SharedCreator::create;
	template < typename... Args > auto
	static inline createSharedThisPtr(Args&&... args) {
		return create(std::forward<Args>(args)...);
	}
};

template <
	typename _Tp,
	typename _Base,
	typename _Deleter = std::default_delete<_Tp>
> struct CreatAsUniqueToBase : private
	UniqueCreator < _Tp, _Base, _Deleter > {
	using UniqueCreator = UniqueCreator < _Tp, _Base, _Deleter >;
	using UniqueCreator::create;
	template < typename... Args > auto
	static inline createUniqueBasePtr(Args&&... args) {
		return create(std::forward<Args>(args)...);
	}
};

template <
	typename _Tp,
	typename _Deleter = std::default_delete<_Tp>
> struct CreatAsUnique : private
	UniqueCreator < _Tp, _Tp, _Deleter > {
	using UniqueCreator = UniqueCreator < _Tp, _Tp, _Deleter >;
	using UniqueCreator::create;
	template < typename... Args > auto
	static inline createUniqueThisPtr(Args&&... args) {
		return create(std::forward<Args>(args)...);
	}
};

template <
	typename _Tp,
	typename _Base,
	typename _Deleter = std::default_delete<_Tp>
> struct MultiSharedCreator : virtual
	public CreatAsSharedToBase < _Tp, _Base, _Deleter >,
	public CreatAsShared < _Tp, _Deleter > {
};

#endif /* CREATEASPOINTER_HPP_ */
