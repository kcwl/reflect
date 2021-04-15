# reflection
一个很cool的静态反射

## reflection 使用方法
reflection库 使用起来很方便，只需要定义一个struct或者class，进行reflect register就可以静态反射。


### reflection API
	使用API之前，需要使用`REFLECT_DEFINE`进行静态反射注册 

	定义于 "reflect.hpp"

	```
	struct test
	{
		REFLECT_DEFINE(
		int a;
		float b;
		char c;)
	};
	```

#### 1. rf_name
	定义于 "reflect.hpp"

##### Example 
	```
	struct test
	{
		REFLECT_DEFINE(
		int a;
		float b;
		char c;)
	}

	auto struct_name = rf_name<test>();

	std::cout << "struct name : " << struct_name << std::endl;
	```

##### Output

	```
	struct name : test
	```

#### 2. rf_size_v
	定义于 "reflect.hpp"

##### Example 
	```
	struct test
	{
		REFLECT_DEFINE(
		int a;
		float b;
		char c;)
	}

	constexpr std::size_t size = rf_size_v<test>;

	std::cout << "struct member size : " << size << std::endl;
	```

##### Output

	```
	struct member size : 3
	```

#### 3. rf_element
	定义于 "reflect.hpp"

##### Example 
	```
	struct test
	{
		REFLECT_DEFINE(
		int a;
		float b;
		char c;)
	}

	test t;
	t.a = 1;
	t.b = 2.0;
	t.c = 'b';

	auto s_1 = rf_element<0>(t);

	auto s_2 = rf_element<1>(t);

	auto s_3 = rf_element<2>(t);

	std::cout <<"struct test's members : \t" <<"member 1:" << s_1 <<"\t member 2:"<< s_2 << "\t member 3:" << s_3 << std::endl << std::endl;
	```

##### Output

	```
	struct test's members : member 1: 1  member 2: 2.000 member 3: b
	```


#### 4. rf_elem_name
	定义于 "reflect.hpp"

##### Example 
	```
	struct test
	{
		REFLECT_DEFINE(
		int a;
		float b;
		char c;)
	}

	auto element_name_0 = rf_elem_name<test,0>();

	auto element_name_1 = rf_elem_name<test,1>();

	auto element_name_2 = rf_elem_name<test,2>();

	std::cout << "struct test's members'name  : \t" << "name 1:" << element_name_0 << "\t name 2:" << element_name_1 << "\t name 3:" << element_name_2 << std::endl;
	```

##### Output

	```
	struct test's members's name : name 1: a  name 2: b name 3: c
	```