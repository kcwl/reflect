#pragma once
#include "reflection/reflect_tuple.hpp"
#include "reflection/detail.hpp"


namespace reflect
{
#define MACRO(...) __VA_ARGS__

#define REFLECT_DEFINE(...)	MACRO(__VA_ARGS__) MAKE_REFLECT(__VA_ARGS__)

	template<size_t N, class T>
	constexpr auto rf_element(T&& val)
	{
		return rf::rf_element<N>(val);
	}

	template<std::size_t N,class T>
	constexpr auto rf_elem_name()
	{
		return rf::rf_elem_name<N,T>();
	}

	template<class T>
	constexpr auto rf_name()
	{
		return rf::rf_name<T>();
	}

	template<std::size_t N, class T>
	using tuple_elemet_t = typename rf::rf_element_type<N, T>::type;

	template<class T>
	inline constexpr static std::size_t rf_size_v = rf::rf_size<T>::value;
}