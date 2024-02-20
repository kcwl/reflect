#pragma once
#include <tuple>
#include <vector>
#include <reflect/concepts.hpp>

namespace reflect
{
	namespace detail
	{
		template<std::size_t N>
		using size_t_ = std::integral_constant<std::size_t, N>;

		struct any_type
		{
			std::size_t ignored;

			template<typename _Ty>
			constexpr operator _Ty() const noexcept
			{
			}
		};

		using multi_range = std::false_type;
		using one_range = std::true_type;

		template<typename _Ty, typename Indice, typename = void>
		struct is_aggregate_initialize_impl : std::false_type {};

		template<typename _Ty, std::size_t... N>
		struct is_aggregate_initialize_impl < _Ty, std::index_sequence<N...>, std::void_t<decltype(_Ty{ any_type{N}... }) >> : std::true_type {};

		template<typename _Ty, std::size_t N>
		struct is_aggregate_initialize : is_aggregate_initialize_impl<_Ty, std::make_index_sequence<N>> {};


		template<typename _Ty, std::size_t N>
		inline constexpr bool is_aggregate_initialize_v = is_aggregate_initialize<_Ty, N>::value;


		template<std::size_t Start, std::size_t End>
		using is_one_element_range = std::integral_constant<bool, Start == End>;

		template<typename _Ty, std::size_t N, typename = std::enable_if_t<is_aggregate_initialize_v<_Ty, N>>>
		using enable_size_t = size_t;

		template<typename _Ty, std::size_t N>
		constexpr auto detect_fields_count_greedy_number(long) noexcept
			-> enable_size_t<_Ty, N>
		{
			return N;
		}

		template<typename _Ty, std::size_t N>
		constexpr std::size_t detect_fields_count_greedy_number(int) noexcept
		{
			return 0;
		}

		template<typename _Ty, std::size_t Start, std::size_t End>
		constexpr std::size_t detect_fields_greey(one_range, long)
		{
			static_assert(Start == End, "binary search error");

			return detect_fields_count_greedy_number<_Ty, Start>(1L);
		}

		template<typename _Ty, std::size_t Begin, std::size_t End>
		constexpr std::size_t detect_fields_greey(multi_range, int);

		template<typename _Ty, std::size_t Begin, std::size_t End>
		constexpr auto detect_fields_greey(multi_range, long)
			-> enable_size_t<_Ty, End>
		{
			constexpr std::size_t next = End + (End - Begin + 1) / 2;
			//向大寻找
			return detect_fields_greey<_Ty, End, next>(is_one_element_range<End, next>{}, 1L);
		}

		template<typename _Ty, std::size_t Begin, std::size_t End>
		constexpr std::size_t detect_fields_greey(multi_range, int)
		{
			//向小寻找
			constexpr std::size_t middle = Begin + (End - Begin) / 2;

			return detect_fields_greey<_Ty, Begin, middle>(is_one_element_range<Begin, middle>{}, 1L);
		}

		template<typename _Ty, std::size_t N>
		constexpr std::size_t detect_fields_count_impl(size_t_<N>)
		{
			return detect_fields_greey<_Ty, 0, N>(multi_range{}, 1L);
		}


		template<pod_t _Ty>
		constexpr std::size_t detect_fields_count()
		{
			constexpr std::size_t max_count = sizeof(_Ty) * CHAR_BIT;

			return detect_fields_count_impl<_Ty>(size_t_<max_count>{});
		}

		template<typename _Ty>
		struct tuple_size
		{
			inline constexpr static std::size_t value = detect_fields_count<_Ty>();
		};
	}
}