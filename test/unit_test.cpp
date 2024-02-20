#define BOOST_TEST_MODULE UnitTest
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <reflect.hpp>
#include "generate.h"
#include "no_pod.h"

BOOST_AUTO_TEST_SUITE(reflect)

struct person
{
	REFLECT_REGIST(
	int age; 
	double sex; )
};

struct animal
{
	REFLECT_REGIST(
	uint16_t kind;
	uint32_t knee;
	float bytes;)
};

BOOST_AUTO_TEST_CASE(struct_name)
{
	constexpr std::string_view person_name = reflect::title<person>();

	BOOST_CHECK(person_name.compare("person") == 0);

	constexpr std::string_view element_name_1 = reflect::name<person, 0>();

	BOOST_CHECK(element_name_1.compare("age") == 0);

	constexpr std::string_view element_name_2 = reflect::name<person, 1>();

	BOOST_CHECK(element_name_2.compare("sex") == 0);
}

BOOST_AUTO_TEST_CASE(type)
{
	using element_type_1 = reflect::elemet_t<person, 0>;

	static_assert(std::same_as<element_type_1, int>);

	using element_type_2 = reflect::elemet_t<person, 1>;

	static_assert(std::same_as<element_type_2, double>);
}

BOOST_AUTO_TEST_CASE(size)
{
	constexpr auto size = reflect::tuple_size_v<person>;

	BOOST_CHECK(size == 2);
}

BOOST_AUTO_TEST_CASE(value)
{
	person p{};
	p.age = 1;
	p.sex = 2.2;

	auto value_1 = reflect::get<0>(p);

	BOOST_CHECK(value_1 == 1);

	auto value_2 = reflect::get<1>(p);

	BOOST_CHECK(value_2 == 2.2);
}

BOOST_AUTO_TEST_SUITE_END()