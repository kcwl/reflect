#pragma once

#define REFLECT_EXPAND(...) __VA_ARGS__

#define REFLECT_CAT1(a, b) a##_##b
#define REFLECT_CAT(a, b) REFLECT_CAT1(a, b)

#define REFLECT_RSEQ_N()                                                                                              \
	31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define REFLECT_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, \
					   _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, N, ...)                                       \
	N

#define REFLECT_NARG_(...) REFLECT_EXPAND(REFLECT_ARG_N(__VA_ARGS__))
#define REFLECT_NARG(...) REFLECT_EXPAND(REFLECT_NARG_(__VA_ARGS__, REFLECT_RSEQ_N()))

#define REFLECT_BIND_IMPL_1(element) #element
#define REFLECT_BIND_IMPL_2(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_1(__VA_ARGS__))
#define REFLECT_BIND_IMPL_3(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_2(__VA_ARGS__))
#define REFLECT_BIND_IMPL_4(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_3(__VA_ARGS__))
#define REFLECT_BIND_IMPL_5(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_4(__VA_ARGS__))
#define REFLECT_BIND_IMPL_6(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_5(__VA_ARGS__))
#define REFLECT_BIND_IMPL_7(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_6(__VA_ARGS__))
#define REFLECT_BIND_IMPL_8(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_7(__VA_ARGS__))
#define REFLECT_BIND_IMPL_9(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_8(__VA_ARGS__))
#define REFLECT_BIND_IMPL_10(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_9(__VA_ARGS__))
#define REFLECT_BIND_IMPL_11(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_10__VA_ARGS__))
#define REFLECT_BIND_IMPL_12(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_11(__VA_ARGS__))
#define REFLECT_BIND_IMPL_13(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_12(__VA_ARGS__))
#define REFLECT_BIND_IMPL_14(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_13(__VA_ARGS__))
#define REFLECT_BIND_IMPL_15(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_14(__VA_ARGS__))
#define REFLECT_BIND_IMPL_16(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_15(__VA_ARGS__))
#define REFLECT_BIND_IMPL_17(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_16(__VA_ARGS__))
#define REFLECT_BIND_IMPL_18(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_17(__VA_ARGS__))
#define REFLECT_BIND_IMPL_19(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_18(__VA_ARGS__))
#define REFLECT_BIND_IMPL_20(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_19(__VA_ARGS__))
#define REFLECT_BIND_IMPL_21(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_20(__VA_ARGS__))
#define REFLECT_BIND_IMPL_22(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_21(__VA_ARGS__))
#define REFLECT_BIND_IMPL_23(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_22(__VA_ARGS__))
#define REFLECT_BIND_IMPL_24(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_23(__VA_ARGS__))
#define REFLECT_BIND_IMPL_25(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_24(__VA_ARGS__))
#define REFLECT_BIND_IMPL_26(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_25(__VA_ARGS__))
#define REFLECT_BIND_IMPL_27(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_26(__VA_ARGS__))
#define REFLECT_BIND_IMPL_28(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_27(__VA_ARGS__))
#define REFLECT_BIND_IMPL_29(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_28(__VA_ARGS__))
#define REFLECT_BIND_IMPL_30(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_29(__VA_ARGS__))
#define REFLECT_BIND_IMPL_31(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_30(__VA_ARGS__))
#define REFLECT_BIND_IMPL_32(element, ...) #element, REFLECT_EXPAND(REFLECT_BIND_IMPL_31(__VA_ARGS__))

#define REFLECT_BIND(...)                                                                                         \
	REFLECT_EXPAND(REFLECT_CAT(REFLECT_BIND_IMPL, REFLECT_NARG(__VA_ARGS__))(__VA_ARGS__))