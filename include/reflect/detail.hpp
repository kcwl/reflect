#pragma once
#include <string_view>
#include <array>


namespace reflect
{
	namespace detail
	{
		template<typename _Ty>
		constexpr std::string_view feild_name()
		{
			using namespace std::string_view_literals;

#ifndef __linux
			constexpr std::string_view name = __FUNCSIG__ ""sv;

			constexpr auto left_bracket = name.find_last_of("<");

			constexpr auto end_bracket = name.find_last_of(">");

			constexpr auto temp_name = name.substr(left_bracket + 1, end_bracket - left_bracket - 1);

			constexpr auto start = temp_name.find_last_of(" ");

			if constexpr (start == std::string_view::npos)
			{
				return temp_name;
			}
			else
			{
				constexpr auto namespace_name = temp_name.substr(start + 1, end_bracket - start - 1);

				constexpr auto last = namespace_name.find_last_of(":");

				if constexpr (last != std::string_view::npos)
					return namespace_name.substr(last + 1);
				else
				{
					return namespace_name;
				}
			}
#else
			constexpr std::string_view name = __PRETTY_FUNCTION__;

			constexpr auto left_bracket = name.find_last_of("[");
			constexpr auto right_bracket = name.find_last_of("]");
			constexpr auto name_in_bracket = name.substr(left_bracket + 1, right_bracket - left_bracket - 1);

			constexpr auto left_equ = name_in_bracket.find_first_of("=");
			constexpr auto right_f = name_in_bracket.find_first_of(";");

			constexpr auto first_name = name_in_bracket.substr(left_equ + 2, right_f - left_equ - 2);

			constexpr auto sp = first_name.find_last_of(":");

			if constexpr (sp == std::string_view::npos)
			{
				return first_name;
			}
			else
			{
				return first_name.substr(sp + 1);
			}
#endif
		}

		template<typename _Ty, std::size_t N>
		constexpr std::size_t find_n_of()
		{
			std::size_t pos = 0;
			constexpr auto member = _Ty::member_str();

			int i = N + 1;
			for (; i > 0; i--)
			{
				pos = member.find_first_of(";", pos + 1);
			}

			return pos;
		}

		template<typename _Ty, std::size_t Index>
		constexpr auto get()
		{
			constexpr auto member_info = _Ty::member_str();

			constexpr std::size_t pos = member_info.find_first_of(";", find_n_of<_Ty, Index>());

			constexpr std::string_view s = member_info.substr(find_n_of<_Ty, Index - 1>() + 1, pos - find_n_of<_Ty, Index - 1>() - 1);

			constexpr std::string_view result = s.substr(s.rfind(" ") + 1);

			return result;
		}

		template<typename _Ty, std::size_t... I>
		constexpr auto split_impl(std::index_sequence<I...>)
		{
			return std::array{ detail::get<_Ty, I>()... };
		}

		template<typename _Ty, std::size_t N, typename _Indices = std::make_index_sequence<N>>
		constexpr auto split()
		{
			return split_impl<_Ty>(_Indices{});
		}
	}
}
