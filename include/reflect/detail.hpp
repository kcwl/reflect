#pragma once
#include <string_view>

namespace reflect
{
	namespace detail
	{
		using namespace std::string_view_literals;

		template<typename T>
		constexpr std::string_view feild_name()
		{
			constexpr std::string_view name = __FUNCSIG__""sv;

			return name.substr(109, name.size() - 116);
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
			return std::make_tuple(get<_Ty, I>()...);
		}

		template<typename _Ty, std::size_t N, typename Indices = std::make_index_sequence<N>>
		constexpr auto split()
		{
			return split_impl<_Ty>(Indices{});
		}

		template<typename _Ty>
		constexpr std::size_t size()
		{
			std::size_t pos = 0;
			std::size_t count = 0;
			constexpr auto member = _Ty::member_str();

			for (;;)
			{
				pos = member.find_first_of(";", pos + 1);
				if (pos == std::string_view::npos)
					break;

				count++;
			}

			return count;
		}
	}
}