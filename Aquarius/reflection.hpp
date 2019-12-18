#pragma once
#include <Aquarius/reflection/reflect_tuple.hpp>


namespace Aquarius
{
	namespace reflection
	{
		#define make_reflect_tuple(struct_name,...)	make_reflect(struct_name,__VA_ARGS__)
	}
}