#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

class vec3f;

class quat {
	float x, y, z, w;

	quat(void);
	quat(float X, float Y, float Z, float W);

	inline float length();

	quat normalized();
	quat conjugate();
	
	bool operator==(const quat& q) const;
	bool operator!=(const quat& q) const;
	quat operator*(const quat& q) const;
	quat operator*(const vec3f& v) const;
	quat operator*(float s) const;
	quat operator/(float s) const;
};