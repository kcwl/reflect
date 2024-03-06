#pragma once
#include <concepts>

namespace reflect
{
	template <typename _Ty>
	concept tuple_t = requires() { std::tuple_size<_Ty>(); };

	template<typename _Ty>
	concept container_t = requires(_Ty value)
	{
		std::begin(value);
		std::end(value);
		typename _Ty::value_type;
		typename _Ty::size_type;
		typename _Ty::allocator_type;
		typename _Ty::iterator;
		typename _Ty::const_iterator;
		value.size();
	};

	template<typename _Ty>
	concept no_container_t = !container_t<_Ty>;

	template <typename _Ty>
	concept single_t = std::is_class_v<std::remove_reference_t<_Ty>> && no_container_t<std::remove_reference_t<_Ty>>;
}