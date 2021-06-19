#pragma once
#include <tuple>
#include <vector>
#include "type_traits.hpp"

namespace reflect
{
	namespace rf
	{
		template<std::size_t N>
		using size_t_ = std::integral_constant<std::size_t, N>;

		struct any_type
		{
			std::size_t ignored_;

			template<typename T>
			constexpr operator T() const noexcept
			{
			}
		};

		using multi_range = std::false_type;
		using one_range = std::true_type;

		template<typename T, typename Indice, typename = void>
		struct is_aggregate_initialize_impl : std::false_type {};

		template<typename T, std::size_t... N>
		struct is_aggregate_initialize_impl < T, std::index_sequence<N...>, std::void_t<decltype(T{ any_type{N}... }) >> : std::true_type {};

		template<typename T, std::size_t N>
		struct is_aggregate_initialize : is_aggregate_initialize_impl<T, std::make_index_sequence<N>>{};


		template<typename T, std::size_t N>
		inline constexpr bool is_aggregate_initialize_v = is_aggregate_initialize<T, N>::value;


		template<std::size_t Start, std::size_t End>
		using is_one_element_range = std::integral_constant<bool, Start == End>;

		template<typename T, std::size_t N, typename = std::enable_if_t<is_aggregate_initialize_v<T, N>>>
		using enable_size_t = size_t;

		template<typename T, std::size_t N>
		constexpr auto detect_fields_count_greedy_number(long) noexcept
			-> enable_size_t<T, N>
		{
			return N;
		}

		template<typename T, std::size_t N>
		constexpr std::size_t detect_fields_count_greedy_number(int) noexcept
		{
			return 0;
		}

		template<typename T, std::size_t Start, std::size_t End>
		constexpr std::size_t detect_fields_greey(one_range, long)
		{
			static_assert(Start == End, "binary search error");

			return detect_fields_count_greedy_number<T, Start>(1L);
		}

		template<typename T, std::size_t Begin, std::size_t End>
		constexpr std::size_t detect_fields_greey(multi_range, int);

		template<typename T, std::size_t Begin, std::size_t End>
		constexpr auto detect_fields_greey(multi_range, long)
			-> enable_size_t<T, End>
		{
			constexpr std::size_t next = End + (End - Begin + 1) / 2;
			//向大寻找
			return detect_fields_greey<T, End, next>(is_one_element_range<End, next>{}, 1L);
		}

		template<typename T, std::size_t Begin, std::size_t End>
		constexpr std::size_t detect_fields_greey(multi_range, int)
		{
			//向小寻找
			constexpr std::size_t middle = Begin + (End - Begin) / 2;

			return detect_fields_greey<T, Begin, middle>(is_one_element_range<Begin, middle>{}, 1L);
		}

		template<typename T, std::size_t N>
		constexpr std::size_t detect_fields_count_impl(size_t_<N>)
		{
			return detect_fields_greey<T, 0, N>(multi_range{}, 1L);
		}


		template<typename T>
		requires(!detail::is_container_v<T>)
		constexpr std::size_t detect_fields_count()
		{
			constexpr std::size_t max_count = sizeof(T) * CHAR_BIT;

			return detect_fields_count_impl<T>(size_t_<max_count>{});
		}

		template<typename T>
		requires(detail::is_container_v<T>)
		constexpr std::size_t detect_fields_count()
		{
			return 1;
		}

		template<typename T>
		struct rf_size
		{
			inline constexpr static std::size_t value = detect_fields_count<T>();
		};
	}
}