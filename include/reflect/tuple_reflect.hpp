#pragma once
#include <tuple>
#include <type_traits>
#include <string_view>
#include "reflect/tuple_size.hpp"
#include "tuple_generated.hpp"
#include "detail.hpp"

namespace reflect
{
	namespace rf
	{
		template<std::size_t N, typename T>
		constexpr auto translate_tuple(T& val)
		{
			return detail::make_tuple(val, size_t_<N>{});
		}

		template<typename T>
		constexpr auto rf_name() -> std::string_view
		{
			return reflect::detail::template feild_name<T>();
		}

		template<std::size_t N, typename T>
		constexpr auto rf_element(const T& val)
		{
			return std::get<N>(rf::translate_tuple<rf_size<T>::value>(val));
		}

		template<typename T, std::size_t N>
		constexpr auto rf_elem_name()
		{
			return std::get<N>(decltype(T::template make_reflect_member<T>())::apply_member());
		}

		template<typename T, std::size_t N>
		struct rf_elem_type
		{
			using type = decltype(rf::rf_element<N>(T{}));
		};

#define MAKE_REFLECT(...)	\
		template<typename _Ty>\
		static auto make_reflect_member()\
		{\
			struct reflect_member\
			{\
				inline constexpr static auto member_str()\
				{\
					return std::string_view(#__VA_ARGS__,sizeof(#__VA_ARGS__) - 1);\
				}\
				inline constexpr decltype(auto) static apply_member()\
				{\
					return reflect::detail::template split<reflect_member,reflect::template rf_size_v<_Ty>>();\
				}\
			};\
			return reflect_member{};\
		}
	}
}