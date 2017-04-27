#include "mat4f.h"

mat4f::mat4f() {}

mat4f mat4f::identity() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mat[i][j] = j == i ? 1 : 0;
		}
	}
	return *this;
}

mat4f mat4f::translate(float x, float y, float z) {
	*this = identity();
	mat[0][3] = x;
	mat[1][3] = y;
	mat[2][3] = z;
	return *this;
}

mat4f mat4f::scale(float x, float y, float z) {
	*this = identity();
	mat[0][0] = x;
	mat[1][1] = y;
	mat[2][2] = z;
	return *this;
}

mat4f mat4f::operator*(const mat4f& m) const {
	mat4f res;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res.mat[i][j] = mat[i][0] * m.mat[0][j] +
				mat[i][1] * m.mat[1][j] +
				mat[i][2] * m.mat[2][j] +
				mat[i][3] * m.mat[3][j];
		}
	}
	return res;
}