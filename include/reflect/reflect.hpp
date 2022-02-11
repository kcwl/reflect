#pragma once
#include <tuple>
#include <type_traits>
#include <string_view>
#include "size.hpp"
#include "generated.hpp"
#include "detail.hpp"


namespace reflect
{
	template<typename T, std::size_t N>
	struct rf_elem_type
	{
		using type = decltype(rf_element<N>(std::declval<T>()));
	};

	template<typename T, std::size_t N>
	using rf_elemet_t = typename rf_elem_type<T, N>::type;

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
				return reflect::template split<reflect_member,rf::template rf_size<_Ty>::value>();\
			}\
		};\
		return reflect_member{};\
	}

#define MACRO(...) __VA_ARGS__

#define REFLECT_DEFINE(...)	MACRO(__VA_ARGS__) MAKE_REFLECT(__VA_ARGS__)

	template<typename T>
	inline constexpr static std::size_t rf_size_v = rf::rf_size<T>::value;

	template<typename T>
	constexpr auto rf_name()
	{
		return rf::template feild_name<T>();
	}

	template<size_t N, typename T>
	constexpr auto rf_element(const T& val)
	{
		return std::get<N>(rf::template make_tuple(val, rf::size_t_<rf_size_v<T>>{}));
	}

	template<typename T, std::size_t N>
	constexpr auto rf_elem_name() -> std::string_view
	{
		return std::get<N>(decltype(T::template make_reflect_member<T>())::apply_member());
	}
}