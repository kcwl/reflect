#pragma once
#include "reflect/generated.hpp"
#include "reflect/size.hpp"
#include <utility>

namespace reflect
{
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