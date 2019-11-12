#pragma once
#include <tuple>
#include <type_traits>
#include <string_view>
#include <vector>
#include "tuple_generated.hpp"


namespace
{
	template<class Tuple, std::size_t N = std::tuple_size<Tuple>::value, class Indices = std::make_index_sequence<N>>
	auto to_array(Tuple&& arr)
	{
		return to_tuple(std::forward<Tuple>(arr), Indices{});
	}

	template<class Tuple, std::size_t... I>
	auto to_array(Tuple&& tuple, std::index_sequence<I...>)->std::array<typename std::tuple_element<0, typename std::remove_reference<Tuple>::type>::type, sizeof...(I)>
	{
		return { { std::get<I>(std::forward<Tuple>(tuple))... } };
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

	template<class T, std::size_t... N>
	decltype(auto) to_tuple(const std::vector<T>& vec, std::index_sequence<N...>)
	{
		return std::make_tuple(vec[N]...);
	}

	template<class T, std::size_t N = 32, class Indices = std::make_index_sequence<N>>
	auto to_tuple(const std::vector<T>& vec)
	{
		return to_tuple(vec, Indices{});
	}

	template<size_t N, class T>
	constexpr auto as_tuple(T& val)
	{
		return reflection::tie_as_tuple(val, reflection::size_t_<N>{});
	}
}

namespace reflection
{
	constexpr int get_string_count_of(const char* str, int length)
	{
		if (length == 0)
			return 0;

		int count = 0;
		
		for (int i = 0; i < length; i++)
		{
			if (str[i] == ',')
				count++;
		}

		return ++count;
	}

#define get_string_count(str)	\
	reflection::get_string_count_of(str,sizeof(str))

	template<std::size_t N>
	constexpr decltype(auto) spilt_string(const char* str)
	{
		std::string_view s(str);

		std::size_t pos = 0;

		std::vector<std::string_view> vec;

		while ((pos = s.find(",")) != std::string_view::npos)
		{
			auto str_single = s.substr(0, pos);

			s = s.substr(pos + 1);

			vec.push_back(str_single);
		}

		vec.push_back(s);

		return to_tuple<std::string_view,N>(vec);
	}

#define make_reflect(struct_name,...)	\
	static auto make_reflect_member(struct_name const&)	\
	{	\
		struct reflect_member	\
		{	\
			using type = void;	\
			constexpr decltype(auto) static apply_member()	\
			{	\
				return reflection::spilt_string<get_string_count(#__VA_ARGS__)>(#__VA_ARGS__);	\
			}	\
			using size_type = std::integral_constant<size_t, get_string_count(#__VA_ARGS__)>;	\
			constexpr static std::string_view name() { return std::string_view(#struct_name,sizeof(#struct_name)); }	\
			constexpr static std::size_t size() { return size_type::value; }	\
		};	\
		return reflect_member{};	\
	}

#define make_reflect_tuple(struct_name,...)	\
	constexpr inline auto tuple_##struct_name = std::make_tuple(#__VA_ARGS__);	\
	make_reflect(struct_name,__VA_ARGS__)

	template<std::size_t N,class T>
	constexpr decltype(auto) get(T&& t)
	{
		using M = decltype(make_reflect_member(std::forward<T>(t)));

		return std::get<N>(M::apply_member());
		//return std::forward<T>(t).*(std::get<N>(M::apply_member()));
	}

	template<size_t N,class T>
	constexpr auto get_element(const T& val)
	{
		auto m = make_reflect_member(T{});
		constexpr std::size_t size = m.size();
		return std::get<N>(as_tuple<size>(val));
	}
}