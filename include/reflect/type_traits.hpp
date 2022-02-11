#pragma once

namespace reflect
{
	template<typename T, typename _ = std::void_t<>>
	struct is_container : std::false_type{};

	template<typename T>
	struct is_container<T, std::void_t<
		typename T::value_type,
		typename T::size_type,
		typename T::allocator_type,
		typename T::iterator,
		typename T::const_iterator,
		decltype(std::declval<T>().size()),
		decltype(std::declval<T>().begin()),
		decltype(std::declval<T>().end()),
		decltype(std::declval<T>().cbegin()),
		decltype(std::declval<T>().cend())>> : std::true_type{};

	template<typename T>
	constexpr static inline bool is_container_v = is_container<T>::value;
}