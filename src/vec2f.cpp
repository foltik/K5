#include "vec2f.h"

vec2f::vec2f() {}

vec2f::vec2f(float X, float Y) {
	x = X;
	y = Y;
}

vec2f::vec2f(float XY) {
	x = y = XY;
}

void vec2f::Init(float X, float Y) {
	x = X;
	y = Y;
}

void vec2f::Zero() {
	x = y = 0.0f;
}

bool vec2f::isValid() const {
	return x == x && y == y;
}

inline float vec2f::length() { return std::sqrt(x * x + y * y); }

inline float vec2f::dot(vec2f v) { return (x * v.x) + (y * v.y); }

vec2f vec2f::normalized() {
	return *this / length();
}

vec2f vec2f::rotated(float angle) {
	// Convert angle to radians
	angle *= M_PI / 180;
	float sin = std::sin(angle);
	float cos = std::cos(angle);
	return vec2f(x * cos - y * sin, x * sin + y * cos);
}

inline bool vec2f::operator==(const vec2f& v) const {
	return (x == v.x && y == v.y);
}

inline bool vec2f::operator!=(const vec2f& v) const {
	return (x != v.x && y != v.y);
}

inline vec2f vec2f::operator-(void) const {
	return vec2f(-x, -y);
}

inline vec2f vec2f::operator-(const vec2f& v) const {
	vec2f res;
	res.x = x - v.x;
	res.y = y - v.y;
	return res;
}

inline vec2f vec2f::operator+(const vec2f& v) const {
	vec2f res;
	res.x = x + v.x;
	res.y = y + v.y;
	return res;
}

inline vec2f vec2f::operator*(float s) const {
	vec2f res;
	res.x = x * s;
	res.y = y * s;
	return res;
}

inline vec2f vec2f::operator*(const vec2f& v) const {
	vec2f res;
	res.x = x * v.x;
	res.y = y * v.y;
	return res;
}

inline vec2f operator*(float s, const vec2f& v) {
	return v * s;
}

inline vec2f vec2f::operator/(float s) const {
	vec2f res;
	res.x = x / s;
	res.y = y / s;
	return res;
}

inline vec2f vec2f::operator/(const vec2f& v) const {
	vec2f res;
	res.x = x / v.x;
	res.y = y / v.y;
	return res;
}