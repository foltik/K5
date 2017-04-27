#pragma once
#include "vec3f.h"

class vertex3f {
public:
	vertex3f(vec3f POS);

	static const int size = 3;
	vec3f pos;
};