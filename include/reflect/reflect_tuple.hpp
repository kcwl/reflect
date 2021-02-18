#pragma once
#include <tuple>
#include <type_traits>
#include <string_view>
#include "reflect/tuple_size.hpp"
#include "tuple_generated.hpp"


namespace reflect
{
	namespace rf
	{
		template<std::size_t N, class T>
		constexpr auto translate_tuple(T& val)
		{
			return detail::make_tuple(val, size_t_<N>{});
		}

		template<class T>
		constexpr auto rf_name()
		{
			return T::template make_reflect_member<T>().name();
		}

		template<std::size_t N, class T>
		constexpr auto rf_element(const T& val)
		{
			return std::get<N>(translate_tuple<rf_size<T>::value>(val));
		}

		template<std::size_t N, class T>
		requires(std::is_same_v<T, std::vector<int>>)
		constexpr auto rf_element(const T& val)
		{
			return val;
		}

		template<std::size_t N, class... Args>
		constexpr auto rf_element(std::tuple<Args...>&& tuple)
		{
			return std::get<N>(tuple);
		}

		template<std::size_t N, class T>
		constexpr auto rf_elem_name()
		{
			return std::get<N>(decltype(T::template make_reflect_member<T>())::apply_member());
		}

		template<std::size_t N, class T>
		struct rf_element_type
		{
			using type = decltype(rf_element<N>(T{}));
		};

#define MAKE_REFLECT(...)	\
    template<class _Ty>\
	static auto make_reflect_member()\
	{\
		struct reflect_member\
		{\
            inline constexpr static auto size(){ return reflect::rf::template rf_size<_Ty>::value; }\
            inline constexpr static auto member_str()\
            {\
	            return std::string_view(#__VA_ARGS__,sizeof(#__VA_ARGS__) - 1);\
	        }\
			inline constexpr decltype(auto) static apply_member()\
			{\
				return detail::template split<reflect_member,size()>();\
			}\
			inline constexpr static std::string_view name() { return detail::template feild_name<_Ty>(); }\
		};\
		return reflect_member{};\
	}
	}
}