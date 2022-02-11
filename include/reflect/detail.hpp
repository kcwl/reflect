#pragma once
#include <string_view>


namespace reflect
{
	namespace rf
	{
		template<typename T>
		constexpr std::string_view feild_name()
		{
			using namespace std::string_view_literals;
			std::size_t start_pos = 0;
			std::size_t length = 0;
#ifdef _MSC_VER
			constexpr std::string_view name = __FUNCSIG__""sv;
			start_pos = 105;
			length = name.size() - 112;
#elif __GNUC__
			constexpr std::string_view name = __PRETTY_FUNCTION__;
			start_pos = 50;
			length = name.size() - 100;
#endif
			return name.substr(start_pos, length);
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

		template<typename _Ty, std::size_t _Index>
		constexpr auto get()
		{
			constexpr auto member_info = _Ty::member_str();

			constexpr std::size_t pos = member_info.find_first_of(";", find_n_of<_Ty, _Index>());

			constexpr std::string_view s = member_info.substr(find_n_of<_Ty, _Index - 1>() + 1, pos - find_n_of<_Ty, _Index - 1>() - 1);

			constexpr std::string_view result = s.substr(s.rfind(" ") + 1);

			return result;
		}

		template<typename _Ty, std::size_t... I>
		constexpr auto split_impl(std::index_sequence<I...>)
		{
			return std::array{ get<_Ty, I>()... };
		}

		template<typename _Ty, std::size_t N, typename Indices = std::make_index_sequence<N>>
		constexpr auto split()
		{
			return split_impl<_Ty>(Indices{});
		}
	}
}
