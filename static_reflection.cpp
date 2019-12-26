// static_reflection.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <algorithm>
#include "Aquarius/reflection.hpp"

struct test_struct
{
	int a;
	float b;
	char c;
	std::string str;
};

AQUARIUS_REFLECT_DEFINE(test_struct, "a", "b", "c")

int main()
{
	test_struct test;
	test.a = 1;
	test.b = 2;
	test.c = 'b';

	std::cout << "struct's name : " << aquarius::tuple_name<test_struct>() << std::endl;

	constexpr std::size_t size = aquarius::tuple_size_v<test_struct>;

	auto s_1 = aquarius::reflect::tuple_element<0>(test);

	auto s_2 = aquarius::reflect::tuple_element<1>(test);

	auto s_3 = aquarius::reflect::tuple_element<2>(test);

	std::cout <<"struct ll's members : \n" <<"member 1:" << s_1 <<"\nmember 2:"<< s_2 << "\nmember 3:" << s_3 << std::endl << std::endl;

	auto element_name_0 = aquarius::tuple_element_name<0>(test_struct{});

	auto element_name_1 = aquarius::tuple_element_name<1>(test_struct{});

	auto element_name_2 = aquarius::tuple_element_name<2>(test_struct{});

	std::cout << "struct ll's members'name  : \n" << "name 1:" << element_name_0 << "\nname 2:" << element_name_1 << "\nname 3:" << element_name_2 << std::endl;

	std::cin.get();

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
