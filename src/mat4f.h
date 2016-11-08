#pragma once

class mat4f {
public:
	float mat[4][4];

	mat4f(void);

	mat4f identity();
	mat4f translate(float x, float y, float z);
	mat4f scale(float x, float y, float z);

	mat4f operator*(const mat4f& m) const;
};