#pragma once
#include <tuple>
#include <type_traits>
#include <string_view>
#include "algorithm.hpp"


namespace reflect
{
	namespace reflection
	{

#define get_string_count(str)	\
		reflect::algorithm::get_string_count_of(str,sizeof(str))

		template<std::size_t N>
		constexpr decltype(auto) get_tp(const char* str)
		{
			return algorithm::spilt<N>(std::move(str));
		}

#define make_reflect(struct_name,...)	\
	static auto make_reflect_member(struct_name const&)	\
	{	\
		struct reflect_member	\
		{	\
			using type = void;	\
			constexpr decltype(auto) static apply_member()	\
			{	\
				return reflect::reflection::get_tp<get_string_count(#__VA_ARGS__)>(#__VA_ARGS__);	\
			}	\
			using size_type = std::integral_constant<size_t, get_string_count(#__VA_ARGS__)>;	\
			constexpr static std::string_view name() { return std::string_view(#struct_name,sizeof(#struct_name) - 1); }	\
			constexpr static std::size_t size() { return size_type::value; }	\
		};	\
		return reflect_member{};	\
	}

#define make_reflect_tuple(struct_name,...)	\
	make_reflect(struct_name,__VA_ARGS__)

		template<std::size_t N, class T>
		constexpr decltype(auto) get(T&& t)
		{
			using M = decltype(make_reflect_member(std::forward<T>(t)));

			return std::get<N>(M::apply_member());
		}

		template<size_t N, class T>
		constexpr auto get_element(const T& val)
		{
			auto m = make_reflect_member(T{});
			constexpr std::size_t size = m.size();
			return std::get<N>(algorithm::as_tuple<size>(val));
		}

		template<class T>
		constexpr auto get_name()
		{
			auto m = make_reflect_member(T{});

			return m.name();
		}

		template<class T>
		constexpr auto get_member_tp()
		{
			using M = decltype(make_reflect_member(T{}));

			return M::apply_member();
		}

		template<class T>
		auto get_member_pos(const std::string& str)
		{
			auto tp = get_member_tp<T>();

			auto arr = algorithm::to_array(std::move(tp));

			for(auto iter = arr.begin(); iter != arr.end(); ++iter)
			{
				if(*iter == str)
					return std::distance(arr.begin(), iter);
			}

			return 0;
		}
	}
}