#pragma once
#include <Aquarius/reflection/reflect_tuple.hpp>


namespace Aquarius
{
	namespace reflection
	{
		#define AQUARIUS_REFLECT_DEFINE(struct_name,...)	MAKE_REFLECT(struct_name,__VA_ARGS__)
	}
}