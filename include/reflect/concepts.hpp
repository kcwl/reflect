#pragma once
#include <concepts>

namespace reflect
{
	namespace detail
	{
		struct any_type
		{
			std::size_t ignored;

			template<typename _Ty>
			constexpr operator _Ty() const noexcept
			{
			}
		};

		template<typename _Ty, typename Indice, typename = void>
		struct is_aggregate_initialize_impl : std::false_type {};

		template<typename _Ty, std::size_t... N>
		struct is_aggregate_initialize_impl < _Ty, std::index_sequence<N...>, std::void_t<decltype(_Ty{ any_type{N}... }) >> : std::true_type {};

		template<typename _Ty, std::size_t N>
		struct is_aggregate_initialize : is_aggregate_initialize_impl<_Ty, std::make_index_sequence<N>> {};
	}

	template <typename _Ty>
	concept tuple_t = requires() { std::tuple_size<_Ty>(); };

	template<typename _Ty>
	concept container_t = requires(_Ty value)
	{
		std::begin(value);
		std::end(value);
		typename _Ty::value_type;
		typename _Ty::size_type;
		typename _Ty::allocator_type;
		typename _Ty::iterator;
		typename _Ty::const_iterator;
		value.size();
	};

	template<typename _Ty>
	concept no_container_t = !container_t<_Ty>;

	template <typename _Ty>
	concept single_t = std::is_class_v<std::remove_reference_t<_Ty>> && no_container_t<std::remove_reference_t<_Ty>>;

	template<typename _Ty>
	concept aggregate_t = std::is_aggregate_v<_Ty>;

	template<typename _Ty, std::size_t N>
	concept aggregate_initialize_t = detail::is_aggregate_initialize<_Ty, N>::value;
}