#pragma once
#include "reflect/detail.hpp"


#ifndef MAKE_REFLECT
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
#endif

#ifndef EXPEND
#define EXPEND(...) __VA_ARGS__
#endif

#ifndef REFLECT_REGIST
#define REFLECT_REGIST(...)	EXPEND(__VA_ARGS__) MAKE_REFLECT(__VA_ARGS__)
#endif