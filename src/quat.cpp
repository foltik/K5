#include "quat.h"
#include "vec3f.h"

quat::quat(void) {}

quat::quat(float X, float Y, float Z, float W) {
	x = X;
	y = Y;
	z = Z;
	w = W;
}

inline float quat::length() {
	return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

quat quat::normalized() {
	return *this / length();
}

quat quat::conjugate() {
	return quat(-x, -y, -z, w);
}

#pragma region Operator Overloads
inline bool quat::operator==(const quat& q) const {
	return (x == q.x && y == q.y && z == q.z && w == q.w);
}

inline bool quat::operator!=(const quat& q) const {
	return (x != q.x && y != q.y && z != q.z && w != q.w);
}

inline quat quat::operator*(const quat& q) const {
	quat res;
	res.x = (x * q.w) + (w * q.x) + (y * q.z) - (z * q.y);
	res.y = (y * q.w) + (w * q.y) + (z * q.x) - (x * q.z);
	res.z = (z * q.w) + (w * q.z) + (x * q.y) - (y * q.x);
	res.w = (w * q.w) - (x * q.x) - (y * q.y) - (z * q.z);
	return res;
}

inline quat quat::operator*(const vec3f& v) const {
	quat res;
	res.x = (w * v.x) + (y * v.z) - (z * v.y);
	res.y = (w * v.y) + (z * v.x) - (x * v.z);
	res.z = (w * v.z) + (x * v.y) - (y * v.x);
	res.w =(-x * v.x) - (y * v.y) - (z * v.z);
	return res;	
}

inline quat quat::operator*(float s) const {
	quat res;
	res.x = x * s;
	res.y = y * s;
	res.z = z * s;
	res.w = w * s;
	return res;
}

inline quat quat::operator/(float s) const {
	quat res;
	res.x = x / s;
	res.y = y / s;
	res.z = z / s;
	res.w = w / s;
	return res;
}
#pragma endregion