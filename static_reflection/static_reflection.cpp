// static_reflection.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "reflect_tuple.hpp"

using namespace reflection;

struct ll
{
	int a;
	int b;
	char c;
};

make_reflect_tuple(ll, a, b, c)

int main()
{
	auto s_1 = reflection::get<0>(ll{});

	auto s_2 = reflection::get<1>(ll{});

	auto s_3 = reflection::get<2>(ll{});

	std::cout <<"struct ll's members : \n" <<"member 1:" << s_1 <<"\nmember 2:"<< s_2 << "\nmember 3:" << s_3 << std::endl;

	ll l;
	l.a = 1;
	l.b = 2;

	auto val = reflection::get_element<1>(l);

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
