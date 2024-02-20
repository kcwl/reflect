#pragma once
#include <concepts>

namespace reflect
{
	template <typename _Ty>
	concept tuple_t = requires() { std::tuple_size<_Ty>(); };

	template <typename _Ty>
	concept class_t = std::is_class_v<std::remove_reference_t<_Ty>>;

	template<typename _Ty>
	concept pod_t = requires()
	{
		std::is_standard_layout_v<std::remove_cvref_t<_Ty>>;
		std::is_trivial_v<std::remove_cvref_t<_Ty>>;
	};

	template<typename _Ty>
	concept no_pod_t = !pod_t<_Ty>;
}