#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

class vec3f {
public:
	float x, y, z;

	vec3f(void);
	vec3f(float X, float Y, float Z);
	vec3f(float XYZ);

	void Init(float X = 0.0f, float Y = 0.0f, float Z = 0.0f);
	void Zero();

	bool isValid() const;

	inline float length();
	inline float dot(vec3f v);
	vec3f normalized();
	vec3f cross(vec3f v);

	bool operator==(const vec3f& v) const;
	bool operator!=(const vec3f& v) const;

	vec3f operator-(void) const;
	vec3f operator+(const vec3f& v) const;
	vec3f operator-(const vec3f& v) const;
	vec3f operator*(const vec3f& v) const;
	vec3f operator/(const vec3f& v) const;
	vec3f operator*(float s) const;
	vec3f operator/(float s) const;
};