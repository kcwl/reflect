# reflection
一个很cool的静态反射

## reflection 使用方法
reflection库 使用起来很方便，只需要定义一个struct或者class，进行reflect register就可以静态反射。


### reflection API
	使用API之前，需要使用`AQUARIUS_REFLECT_DEFINE`进行静态反射注册 

	定义于 "aquarius/reflection.hpp"

	```
	struct test
	{
		int a;
		float b;
		char c;
	};

	AQUARIUS_REFLECT_DEFINE(test, "a", "b", "c")
	```

#### 1. tuple_name
	定义于 "aquarius/reflection.hpp"

	```
	template<class T>
	constexpr auto tuple_name();
	```

##### Example 
	```
	struct test
	{
		int a;
		float b;
		char c;
	}

	auto struct_name = tuple_name<test>();

	std::cout << "struct name : " << struct_name << std::endl;
	```

##### Output

	```
	struct name : test
	```

#### 2. tuple_size_v
	定义于 "aquarius/reflection.hpp"

	```
	template<std::size_t N,class T>
	using tuple_size = reflect::tuple_size<T>;

	template<class T>
	inline constexpr static std::size_t tuple_size_v = reflect::tuple_size<T>::value;
	```

##### Example 
	```
	struct test
	{
		int a;
		float b;
		char c;
	}

	constexpr std::size_t size = aquarius::tuple_size_v<test>;

	std::cout << "struct member size : " << size << std::endl;
	```

##### Output

	```
	struct member size : 3
	```

#### 3. tuple_element
	定义于 "aquarius/reflection.hpp"

	```
	template<size_t N, class T>
	constexpr auto tuple_element(const T& val)
	```

##### Example 
	```
	struct test
	{
		int a;
		float b;
		char c;
	}

	test t;
	t.a = 1;
	t.b = 2.0;
	t.c = 'b';

	auto s_1 = aquarius::reflect::tuple_element<0>(t);

	auto s_2 = aquarius::reflect::tuple_element<1>(t);

	auto s_3 = aquarius::reflect::tuple_element<2>(t);

	std::cout <<"struct test's members : \t" <<"member 1:" << s_1 <<"\t member 2:"<< s_2 << "\t member 3:" << s_3 << std::endl << std::endl;
	```

##### Output

	```
	struct test's members : member 1: 1  member 2: 2.000 member 3: b
	```


#### 4. tuple_element_name
	定义于 "aquarius/reflection.hpp"

	```
	template<std::size_t N,class T>
	constexpr auto tuple_element_name(const T& val)
	```

##### Example 
	```
	struct test
	{
		int a;
		float b;
		char c;
	}

	auto element_name_0 = aquarius::tuple_element_name<0>(test{});

	auto element_name_1 = aquarius::tuple_element_name<1>(test{});

	auto element_name_2 = aquarius::tuple_element_name<2>(test{});

	std::cout << "struct test's members'name  : \t" << "name 1:" << element_name_0 << "\t name 2:" << element_name_1 << "\t name 3:" << element_name_2 << std::endl;
	```

##### Output

	```
	struct test's members's name : name 1: a  name 2: b name 3: c
	```




### 最后
reflection库参考了 [iguaua](https://github.com/qicosmos/iguana)和 [magic_get](https://github.com/apolukhin/magic_get)！ 感谢前辈们的付出，让我们后来者能有站在巨人肩膀上的机会！！！