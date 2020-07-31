#pragma once
#include "reflection/reflect_tuple.hpp"


namespace aquarius
{
	#define AQUARIUS_MEMBER(name) #name 

	#define AQUARIUS_REFLECT_DEFINE(STRUCT,...)	MAKE_TUPLE(STRUCT,__VA_ARGS__)

	template<size_t N, class T>
	constexpr auto tuple_element(const T& val)
	{
		return reflect::tuple_element<N>(val);
	}

	template<std::size_t N,class T>
	constexpr auto tuple_element_name(const T& val)
	{
		return reflect::tuple_element_name<N>(val);
	}

	template<class T>
	constexpr auto tuple_name()
	{
		return reflect::tuple_name<T>();
	}

	template<std::size_t N,class T>
	using tuple_size = reflect::tuple_size<T>;

	template<class T>
	inline constexpr static std::size_t tuple_size_v = reflect::tuple_size<T>::value;
}