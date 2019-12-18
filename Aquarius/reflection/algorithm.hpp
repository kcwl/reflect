#pragma once
#include <utility>
#include <vector>
#include <algorithm>
#include <string_view>
#include <Aquarius/reflection/tuple_generated.hpp>

namespace Aquarius
{
	namespace algorithm
	{
		template<class Tuple, std::size_t... I>
		constexpr auto to_array(Tuple&& tuple, std::index_sequence<I...>) ->std::array<typename std::tuple_element<0, typename std::remove_reference<Tuple>::type>::type, sizeof...(I)>
		{
			return {{ std::get<I>(std::forward<Tuple>(tuple))... }};
		}

		template<class Tuple, std::size_t N = std::tuple_size<Tuple>::value, class Indices = std::make_index_sequence<N>>
		constexpr auto to_array(Tuple&& tp)
		{
			return to_array(std::forward<Tuple>(tp), Indices{});
		}

		template<class Array, std::size_t... I>
		constexpr auto to_tuple(const Array& arr, std::index_sequence<I...>)
		{
			return std::make_tuple(std::get<I>(arr)...);
		}

		template<class T, std::size_t N, class Indices = std::make_index_sequence<N>>
		constexpr auto to_tuple(const std::array<T, N>& arr)
		{
			return to_tuple(arr, Indices{});
		}

		template<size_t N, class T>
		constexpr auto as_tuple(T& val)
		{
			return Aquarius::Generate::tie_as_tuple(val, Aquarius::Generate::size_t_<N>{});
		}

		template<std::size_t N, std::size_t I>
		constexpr std::string_view get(std::string_view&& str)
		{
			if constexpr(I != N - 1)
			{
				str.remove_suffix(str.size() - str.find_last_of(","));
				str.remove_suffix(std::min(str.find_first_not_of(" "), str.size()));
			}

			return str.substr(str.find_last_of(",")+1,str.size());
		}

		template<std::size_t N, std::size_t... I>
		constexpr auto spilt(std::string_view&& str, std::index_sequence<I...>)
		{
			auto remove_prefix = [&](std::string_view s)
			{
				s.remove_prefix(s.find_first_not_of(" "));
				s.remove_suffix(s.size() - 1 - s.find_last_not_of(" "));

				return s;
			};

			return std::make_tuple(remove_prefix(algorithm::get<N, I>(std::forward<std::string_view>(str)))...);
		}

		template<std::size_t N, class Indices = std::make_index_sequence<N>>
		constexpr auto spilt(std::string_view&& str)
		{
			return spilt<N>(std::forward<std::string_view>(str), Indices{});
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