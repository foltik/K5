#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

class vec2f {
public:
	float x, y;

	vec2f(void);
	vec2f(float X, float Y);
	vec2f(float XY);

	void Init(float X = 0.0f, float Y = 0.0f);
	void Zero();

	bool isValid() const;

	inline float length();
	inline float dot(vec2f v);
	
	vec2f normalized();
	vec2f rotated(float angle);

	bool operator==(const vec2f& v) const;
	bool operator!=(const vec2f& v) const;
	vec2f operator-(void) const;
	vec2f operator+(const vec2f& v) const;
	vec2f operator-(const vec2f& v) const;
	vec2f operator*(const vec2f& v) const;
	vec2f operator/(const vec2f& v) const;
	vec2f operator*(float s) const;
	vec2f operator/(float s) const;
};