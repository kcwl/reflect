#pragma once
#include <type_traits>

namespace reflect
{
	namespace detail
	{
		template<typename T,typename = void>
		struct is_container : std::false_type{};

		template<typename T>
		struct is_container<T, 
			std::void_t<decltype(std::declval<T>().begin()), 
			            decltype(std::declval<T>().end()),
		                typename T::value_type>> : std::true_type{ };

		template<typename T>
		constexpr static bool is_container_v = is_container<T>::value;
	}
}