#include "pch.h"
#include "generate.h"
#include "no_pod.h"

struct persons
{
	REFLECT_REGIST(
		int age;
	double sex; )
};

struct animal
{
	REFLECT_REGIST
	(
		uint16_t kind;
	uint32_t knee;
	float bytes;
	)
};

TEST(reflect, name)
{
	std::string_view person_name = reflect::title<persons>();

	EXPECT_EQ(person_name.compare("persons"), 0);

	std::string_view element_name_1 = reflect::name<persons, 0>();

	EXPECT_EQ(element_name_1.compare("age"), 0);

	std::string_view element_name_2 = reflect::name<persons, 1>();

	EXPECT_EQ(element_name_2.compare("sex"), 0);
}

TEST(reflect, type)
{
	using element_type_1 = reflect::elemet_t<persons, 0>;

	EXPECT_TRUE((std::same_as<element_type_1, int>));

	using element_type_2 = reflect::elemet_t<persons, 1>;

	EXPECT_TRUE((std::same_as<element_type_2, double>));
}

TEST(reflect, size)
{
	auto size = reflect::tuple_size_v<persons>;

	EXPECT_EQ(size, 2);
}

TEST(reflect, value)
{
	persons p{};
	p.age = 1;
	p.sex = 2.2;

	auto value_1 = reflect::get<0>(p);

	EXPECT_EQ(value_1, 1);

	auto value_2 = reflect::get<1>(p);

	EXPECT_EQ(value_2, 2.2);
}