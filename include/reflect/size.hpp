#pragma once
#include <tuple>
#include <vector>
#include "concepts.hpp"

namespace reflect
{
	namespace detail
	{
		constexpr static std::size_t max_size = 31;

		template<std::size_t N>
		using size_t_ = std::integral_constant<std::size_t, N>;

		using multi_range = std::false_type;
		using one_range = std::true_type;

		template<std::size_t Start, std::size_t End>
		using is_one_element_range = std::integral_constant<bool, Start == End>;

		template<typename _Ty, std::size_t Start, std::size_t End>
		constexpr std::size_t detect_fields_greey(one_range, long)
		{
			static_assert(Start == End, "binary search error");

			if constexpr (aggregate_initialize_t<_Ty, Start>)
			{
				return Start;
			}
			else
			{
				return 0;
			}
		}

		template<typename _Ty, std::size_t Begin, std::size_t End>
		constexpr std::size_t detect_fields_greey(multi_range, int)
		{
			if constexpr (aggregate_initialize_t<_Ty, End>)
			{
				constexpr std::size_t next = End + (End - Begin + 1) / 2;
				//向大寻找
				return detect_fields_greey<_Ty, End, next>(is_one_element_range<End, next>{}, 1L);
			}
			else
			{
				//向小寻找
				constexpr std::size_t middle = Begin + (End - Begin) / 2;

				return detect_fields_greey<_Ty, Begin, middle>(is_one_element_range<Begin, middle>{}, 1L);
			}
		}

		template<typename _Ty, std::size_t N>
		constexpr std::size_t detect_fields_count_impl(size_t_<N>)
		{
			return detect_fields_greey<_Ty, 0, N>(multi_range{}, 1L);
		}


		template<aggregate_t _Ty>
		constexpr std::size_t detect_fields_count()
		{
			return detect_fields_count_impl<_Ty>(size_t_<max_size>{});
		}

		template<typename _Ty>
		constexpr std::size_t detect_fields_count()
		{
			return 1;
		}

		template<typename _Ty>
		struct tuple_size
		{
			inline constexpr static std::size_t value = detect_fields_count<_Ty>();
		};
	}

	template<typename _Ty>
	constexpr static std::size_t tuple_size_v = detail::tuple_size<_Ty>::value;
}