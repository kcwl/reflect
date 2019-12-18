#pragma once
#include <tuple>
#include <type_traits>
#include <string_view>
#include <Aquarius/reflection/algorithm.hpp>


namespace Aquarius
{
	namespace reflection
	{

#define get_string_count(str)	\
		Aquarius::algorithm::get_string_count_of(str,sizeof(str))

#define MAKE_REFLECT(STRUCT,...)	\
		static auto make_reflect_member(STRUCT const&)	\
		{	\
			struct reflect_member	\
			{	\
				constexpr decltype(auto) static apply_member()	\
				{	\
					return Aquarius::reflection::get_tp<get_string_count(#__VA_ARGS__)>(#__VA_ARGS__);	\
				}	\
				using size_type = std::integral_constant<size_t, get_string_count(#__VA_ARGS__)>;	\
				constexpr static std::string_view name() { return std::string_view(#STRUCT,sizeof(#STRUCT) - 1); }	\
				constexpr static std::size_t size() { return size_type::value; }	\
			};	\
			return reflect_member{};	\
		}

		template<std::size_t N, class T>
		constexpr decltype(auto) get(T&& t)
		{
			using M = decltype(make_reflect_member(std::forward<T>(t)));

			return std::get<N>(M::apply_member());
		}

		template<std::size_t N>
		constexpr decltype(auto) get_tp(const char* str)
		{
			return Aquarius::algorithm::spilt<N>(std::move(str));
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
	}
}