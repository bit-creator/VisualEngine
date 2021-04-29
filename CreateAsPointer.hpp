/*
 * lifecicle.hpp
 *
 *  Created on: 20 ���. 2021 �.
 *      Author: IAbernikhin
 */

#ifndef CREATEASPOINTER_HPP_
#define CREATEASPOINTER_HPP_

#include <memory>

template <
	typename _Tp,
	typename _Base,
	typename _Deleter,
	template < typename... >
		typename _Ptr,
	typename... _PtrArgs
> struct CreatorImpl {
	using pointerToBase = _Ptr < _Base, _PtrArgs... >;
	using pointer = _Ptr < _Tp, _PtrArgs... >;
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
	CreatorImpl < _Tp, _Base, _Deleter, std::shared_ptr > {
	using CreatorT = CreatorImpl < _Tp, _Base, _Deleter, std::shared_ptr >;
	using CreatorT::createImpl;
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
	CreatorImpl < _Tp, _Base, _Deleter, std::unique_ptr, _Deleter > {
	using CreatorT = CreatorImpl < _Tp, _Base, _Deleter, std::unique_ptr, _Deleter >;
	using CreatorT::createImpl;
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
	using SharedCreatorT = SharedCreator < _Tp, _Base, _Deleter >;
	using SharedCreatorT::create;
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
	using SharedCreatorT = SharedCreator < _Tp, _Tp, _Deleter >;
	using SharedCreatorT::create;
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
	using UniqueCreatorT = UniqueCreator < _Tp, _Base, _Deleter >;
	using UniqueCreatorT::create;
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
	using UniqueCreatorT = UniqueCreator < _Tp, _Tp, _Deleter >;
	using UniqueCreatorT::create;
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
