# reflect
c++20 static reflect library

## build status
[![codecov](https://codecov.io/gh/kcwl/reflect/graph/badge.svg?token=B1X6HFIFT3)](https://codecov.io/gh/kcwl/reflect)

[![Ubuntu(clang)](https://github.com/kcwl/reflect/actions/workflows/cmake-ubuntu-clang.yml/badge.svg)](https://github.com/kcwl/reflect/actions/workflows/cmake-ubuntu-clang.yml)
[![Ubuntu(gcc)](https://github.com/kcwl/reflect/actions/workflows/cmake-ubuntu-gcc.yml/badge.svg)](https://github.com/kcwl/reflect/actions/workflows/cmake-ubuntu-gcc.yml)
[![Visual Stadio](https://github.com/kcwl/reflect/actions/workflows/cmake-windows-vs.yml/badge.svg)](https://github.com/kcwl/reflect/actions/workflows/cmake-windows-vs.yml)

## introdution
refelct is a static reflect library with c++ 20 that only uses very few codes can complete regist. it is surprise that is header only, so you can use it only include them.

## usage

reflect has provided some functions to complete reflect, there are `refelct::title<T>()`,`reflect::name<T,N>()`,`reflect::get<N<T>(T{})`, 
and one type traits `reflect::elelemnt_t<T,N>`, and some functions likes `for_each`;

|function name| function usage|
||
|`refelct::title<T>()`|return the name of struct T |                   
|`reflect::name<T,N>()`|return the name of Nth element in struct T|
|`reflect::get<N<T>(T{})`|return the value of Nth element in struct T|

some functions like `for_each`, such as below:

```
template <typename _Ty, typename _Func>
constexpr auto for_each(_Ty&& tp, _Func&& f);  //_Func -> _Func<_Ty::value_type /*Nth element value*/)


template <typename _Ty, typename _Func>
constexpr auto for_each_element(_Ty&& tp, _Func&& f);  //_Func -> _Func(std::string_view/*Nth element name*/,_Ty::value_type /*Nth element value*/_, std::size_t /*N*/)
```

one type trait
```
template<typename _Ty, std::size_t N>
using elemet_t = typename element_type<_Ty, N>::type;   // return Nth element type , also can use the basic way that element_type<_Ty.N>::type
```

## example
```
struct person
{
REFLECT_REGIST
(
	int age;
	bool sex;
	std::string name;
)_
};

person pers{1,true,"person"};

constexpr auto tile_value = reflect::title<person>(); // title_value is "person"_

constexpr auto first_value = reflect::get<0>(pers);   // first_value is 1
constexpr auto second_value = reflect::get<1>(pers);  // second_value is true
constexpr auto three_value = reflect::get<2>(pers);   // first_value is "name"

consteexpr auto first_value_name = reflect::name<person,0>(); // first_value_name is "age"
consteexpr auto second_value_name = reflect::name<person,1>(); // second_value_name is "sex"
consteexpr auto third_value_name = reflect::name<person,2>(); // third_value_name is "name"

using first_type = reflect::element_t<person,0>; // first_type is int
using second_type = reflect::element_t<person,1>; // first_type is bool
using third_type = reflect::element_t<person,2>; // first_type is std::string

```

you can scan unit tests for more examples!

## wiki