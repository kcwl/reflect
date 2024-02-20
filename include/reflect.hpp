#pragma once
#include <reflect/generated.hpp>
#include <reflect/size.hpp>
#include <reflect/detail.hpp>
#include <string_view>

namespace reflect
{
	template<typename T, std::size_t N>
	struct element_type
	{
		using type = decltype(get<N>(std::declval<T>()));
	};

	template<typename T, std::size_t N>
	using elemet_t = typename element_type<T, N>::type;

	template<typename _Ty>
	constexpr static std::size_t tuple_size_v = detail::tuple_size<_Ty>::value;

#define MAKE_REFLECT(...)	\
	template<typename _Ty>\
	static auto make_reflect_member()\
	{\
		struct reflect_member\
		{\
			inline constexpr static auto member_str()\
			{\
				return std::string_view(#__VA_ARGS__,sizeof(#__VA_ARGS__) - 1);\
			}\
			inline constexpr decltype(auto) static apply_member()\
			{\
				return reflect::detail::template split<reflect_member,reflect::template tuple_size_v<_Ty>>();\
			}\
		};\
		return reflect_member{};\
	}

	template<typename T>
	constexpr auto title()
	{
		return detail::template feild_name<T>();
	}

	template<size_t N, typename T>
	constexpr auto get(const T& val)
	{
		return std::get<N>(detail::template make_tuple(val, detail::size_t_<tuple_size_v<T>>{}));
	}


	template<typename T, std::size_t N>
	constexpr auto name() -> std::string_view
	{
		return std::get<N>(decltype(T::template make_reflect_member<T>())::apply_member());
	}
}



#define EXPEND(...) __VA_ARGS__

#define REFLECT_REGIST(...)	EXPEND(__VA_ARGS__) MAKE_REFLECT(__VA_ARGS__)