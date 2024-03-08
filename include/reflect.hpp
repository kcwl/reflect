#pragma once
#include "reflect/size.hpp"
#include "reflect/for_each.hpp"
#include "reflect/regist.hpp"
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
	constexpr auto title()
	{
		return detail::template feild_name<_Ty>();
	}
}
