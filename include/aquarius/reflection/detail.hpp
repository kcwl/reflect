#pragma once
#include <utility>
#include <vector>
#include <algorithm>
#include <string_view>
#include "tuple_generated.hpp"

namespace aquarius
{
	namespace detail
	{
		//template<size_t N, class T>
		//constexpr auto make_tuple(T& val)
		//{
		//	return generate::make_tuple(val, generate::size_t_<N>{});
		//}

		//template<std::size_t N, std::size_t I>
		//constexpr std::string_view get(std::string_view&& str)
		//{
		//	if constexpr(I != N - 1)
		//	{
		//		str.remove_suffix(str.size() - str.find_last_of(","));
		//		str.remove_suffix(std::min(str.find_first_not_of(" "), str.size()));
		//	}

		//	return str.substr(str.find_last_of(",")+1,str.size());
		//}

		//template<std::size_t N, std::size_t... I>
		//constexpr auto spilt(std::string_view&& str, std::index_sequence<I...>)
		//{
		//	auto remove_prefix = [&](std::string_view s)
		//	{
		//		s.remove_prefix(s.find_first_not_of(" "));
		//		s.remove_suffix(s.size() - 1 - s.find_last_not_of(" "));

		//		return s;
		//	};

		//	return std::make_tuple(remove_prefix(detail::get<N, I>(std::forward<std::string_view>(str)))...);
		//}

		//template<std::size_t N, class Indices = std::make_index_sequence<N>>
		//constexpr auto spilt(std::string_view&& str)
		//{
		//	return spilt<N>(std::forward<std::string_view>(str), Indices{});
		//}

		//template<std::size_t N>
		//constexpr int count_if(const char(&str)[N],char seq)
		//{
		//	int count_ = 0;
		//	for(int i = 0; i < N; i++)
		//	{
		//		if(str[i] == seq)
		//			count_++;
		//	}

		//	return ++count_;
		//}
	}
}