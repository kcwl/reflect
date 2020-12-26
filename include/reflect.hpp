#pragma once
#include "reflection/reflect_tuple.hpp"
#include "reflection/detail.hpp"


namespace reflect
{
#define MACRO(...) __VA_ARGS__

#define REFLECT_DEFINE(...)	MACRO(__VA_ARGS__) MAKE_REFLECT(__VA_ARGS__)

	template<size_t N, class T>
	constexpr auto rf_element(const T& val)
	{
		return rf::template rf_element<N>(val);
	}

	template<class T, std::size_t N>
	constexpr auto rf_elem_name()
	{
		return rf::rf_elem_name<T,N>();
	}

	template<class T>
	constexpr auto rf_name()
	{
		return rf::rf_name<T>();
	}

	template<class T, std::size_t N>
	using tuple_elemet_t = typename rf::rf_element_type<T, N>::type;

	template<class T>
	inline constexpr static std::size_t rf_size_v = rf::rf_size<T>::value;
}