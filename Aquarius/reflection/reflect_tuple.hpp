#pragma once
#include <tuple>
#include <type_traits>
#include <string_view>
#include <Aquarius/reflection/detail.hpp>
#include "Aquarius/reflection/tuple_size.hpp"


namespace aquarius
{
	namespace reflect
	{
		template<size_t N, class T>
		constexpr auto translate_tuple(T& val)
		{
			return generate::make_tuple(val, generate::size_t_<N>{});
		}

		template<class T>
		constexpr auto tuple_name()
		{
			return make_reflect_member(T{}).name();
		}

		template<size_t N, class T>
		constexpr auto tuple_element(const T& val)
		{
			auto m = make_reflect_member(T{});

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
				inline constexpr static auto size(){ return aquarius::reflect::tuple_size<STRUCT>::value; }	\
				inline constexpr static std::string_view name() { return std::string_view(#STRUCT,sizeof(#STRUCT) - 1); }	\
			};	\
			return reflect_member{};	\
		}
	}
}