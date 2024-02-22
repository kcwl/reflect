#pragma once
#include "reflect/generated.hpp"
#include "reflect/size.hpp"
#include "reflect/detail.hpp"
#include <string_view>

namespace reflect
{
	template<typename _Ty, std::size_t N>
	struct element_type
	{
		using type = decltype(get<N>(std::declval<_Ty>()));
	};

	template<typename _Ty, std::size_t N>
	using elemet_t = typename element_type<_Ty, N>::type;

	template<typename _Ty>
	constexpr static std::size_t tuple_size_v = detail::tuple_size<_Ty>::value;
#ifndef MAKE_REFLECT
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
				return reflect::detail::template split<reflect_member,reflect::template tuple_size_v<_Ty>>();\
			}\
		};\
		return reflect_member{};\
	}
#endif

	template<typename _Ty>
	constexpr auto title()
	{
		return detail::template feild_name<_Ty>();
	}

	template<size_t N, typename _Ty>
	constexpr auto get(const _Ty& val)
	{
		return std::get<N>(detail::template make_tuple(val, detail::size_t_<tuple_size_v<_Ty>>{}));
	}


	template<typename _Ty, std::size_t N>
	constexpr auto name() -> std::string_view
	{
		return std::get<N>(decltype(_Ty::template make_reflect_member<_Ty>())::apply_member());
	}

	template <typename _Tuple, typename _Func, std::size_t... I>
	constexpr auto for_each(_Tuple&& tuple, _Func&& f, std::index_sequence<I...>)
	{
		return (std::forward<_Func>(f)(get<I>(std::forward<_Tuple>(tuple))), ...);
	}

	template <typename _Ty, typename _Func>
	constexpr auto for_each(_Ty&& tp, _Func&& f)
	{
		return for_each(std::forward<_Ty>(tp), std::forward<_Func>(f),
			std::make_index_sequence<tuple_size_v<_Ty>>{});
	}

	template <typename _Tuple, typename _Func, std::size_t... I>
	constexpr auto for_each_element(_Tuple&& tuple, _Func&& f, std::index_sequence<I...>)
	{
		return (std::forward<_Func>(f)(name<_Tuple, I>(), reflect::get<I>(std::forward<_Tuple>(tuple)), std::move(I)),
			...);
	}

	template <typename _Ty, typename _Func>
	constexpr auto for_each_element(_Ty&& tp, _Func&& f)
	{
		return for_each_element(std::forward<_Ty>(tp), std::forward<_Func>(f),
			std::make_index_sequence<reflect::tuple_size_v<_Ty>>{});
	}
}



#define EXPEND(...) __VA_ARGS__

#define REFLECT_REGIST(...)	EXPEND(__VA_ARGS__) MAKE_REFLECT(__VA_ARGS__)