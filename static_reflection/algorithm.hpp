#pragma once
#include <utility>
#include <string_view>
#include <vector>
#include "tuple_generated.hpp"
#include <algorithm>

namespace reflect
{
	namespace algorithm
	{
		template<class Tuple, std::size_t... I>
		auto to_array(Tuple&& tuple, std::index_sequence<I...>)->std::array<typename std::tuple_element<0, typename std::remove_reference<Tuple>::type>::type, sizeof...(I)>
		{
			return {{ std::get<I>(std::forward<Tuple>(tuple))... }};
		}

		//template<class Tuple, std::size_t N = std::tuple_size<Tuple>::value, class Indices = std::make_index_sequence<N>>
		template<class... Args>
		auto to_array(std::tuple<Args...>&& tp)
		{
			using Indices = std::make_index_sequence<sizeof...(Args)>;

			return to_array(std::forward<decltype(tp)>(tp), Indices{});
		}

		template<class Array, std::size_t... I>
		auto to_tuple(const Array& arr, std::index_sequence<I...>)
		{
			return std::make_tuple(arr[I]...);
		}

		template<class T, std::size_t N, class Indices = std::make_index_sequence<N>>
		auto to_tuple(const std::array<T, N>& arr)
		{
			return to_tuple(arr, Indices{});
		}

		template<size_t N, class T>
		constexpr auto as_tuple(T& val)
		{
			return reflection::tie_as_tuple(val, reflection::size_t_<N>{});
		}

		template<std::size_t N, std::size_t I>
		constexpr std::string_view get(std::string_view&& str)
		{
			if constexpr(I != N - 1)
			{
				str.remove_prefix(str.find_first_of(",") + 1);
				str.remove_prefix((std::min)(str.find_first_not_of(" "), str.size()));
			}

			return str.substr(0, str.find_first_of(","));
		}

		template<std::size_t N, std::size_t... I>
		constexpr auto spilt_impl(std::string_view&& str, std::index_sequence<I...>)
		{
			return algorithm::reverse_tuple(std::make_tuple(get<N, I>(std::forward<std::string_view>(str))...));
		}

		template<std::size_t N, class Indices = std::make_index_sequence<N>>
		constexpr auto spilt_string(std::string_view&& str)
		{
			return spilt_impl<N>(std::forward<std::string_view>(str), Indices{});
		}

		template<std::size_t N>
		constexpr auto spilt(std::string_view&& str)
		{
			return spilt_string<N>(std::forward<std::string_view>(str));
		}

		template<class... Args, std::size_t... I>
		constexpr auto reverse_tuple_impl(std::tuple<Args...>&& tp, std::index_sequence<I...>)
		{
			return std::tuple{std::get<sizeof...(Args) - I - 1>(std::forward<decltype(tp)>(tp))...};
		}

		template<class... Args>
		constexpr auto reverse_tuple(std::tuple<Args...>&& tp)
		{
			return reverse_tuple_impl(std::forward<decltype(tp)>(tp), std::make_index_sequence<sizeof...(Args)>{});
		}

		constexpr int get_string_count_of(const char* str, int length)
		{
			if(length == 0)
				return 0;

			int count = 0;

			for(int i = 0; i < length; i++)
			{
				if(str[i] == ',')
					count++;
			}

			return ++count;
		}
	}
}