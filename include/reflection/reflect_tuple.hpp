#pragma once
#include <tuple>
#include <type_traits>
#include <string_view>
#include "reflection/tuple_size.hpp"
#include "tuple_generated.hpp"


namespace reflect
{
	template<std::size_t N, class T>
	constexpr auto translate_tuple(T& val)
	{
		return detail::make_tuple(val, size_t_<N>{});
	}

	template<class T>
	constexpr auto tuple_name()
	{
		return make_reflect_member(T{}).name();
	}

	template<std::size_t N, class T>
	constexpr auto tuple_element(const T& val)
	{
		return std::get<N>(translate_tuple<tuple_size<T>::value>(val));
	}

	template<std::size_t N, class... Args>
	constexpr auto tuple_element(std::tuple<Args...>&& tuple)
	{
		return std::get<N>(tuple);
	}

	template<std::size_t N, class T>
	constexpr auto tuple_element_name(const T&)
	{
		return std::get<N>(decltype(make_reflect_member(T{}))::apply_member());
	}

	template<std::size_t N, class T>
	struct tuple_element_type
	{
		using type = decltype(tuple_element<N>(T{}));
	};


#define AQUARIUS_MEMBER(name) #name 

#define MAKE_TUPLE(STRUCT,...)	\
	static auto make_reflect_member(const STRUCT&)	\
	{	\
		struct reflect_member	\
		{	\
			inline constexpr decltype(auto) static apply_member()	\
			{	\
				return std::make_tuple(__VA_ARGS__);	\
			}	\
			inline constexpr static auto size(){ return reflect::tuple_size<STRUCT>::value; }	\
			inline constexpr static std::string_view name() { return std::string_view(#STRUCT,sizeof(#STRUCT) - 1); }	\
		};	\
		return reflect_member{};	\
	}
}