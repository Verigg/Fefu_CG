#pragma once

#include <cassert>
#include <iostream>
#include <array>
#include <ostream>
#include <vector>
#include <cmath>
#include <cassert>

#include "vec.h"
#include "mat.h"

#define M_PI 3.14159265358979323846

using Vec2 = Vector2;
using Vec3 = Vector3;
using Vec4 = Vector4;

using Mat2 = Matrix2;
using Mat3 = Matrix3;
using Mat4 = Matrix4;

using namespace std;


inline float radians(float degree) {
	return degree * M_PI / 180.0f;
}

//inline float cos(float angle) {
//	return cosf(angle);
//}
//
//inline float sin(float angle) {
//	return sinf(angle);
//}
//
//inline float tan(float angle) {
//	return tanf(angle);
//}

inline Vector3 cross(Vector3 x, Vector3 y) {
	Vector3 out(
		x.y * y.z - y.y * x.z,
		x.z * y.x - y.z * x.x,
		x.x * y.y - y.x * x.y);
	return out;
}

inline Vector3 normalize(Vector3 vec) {
	return { vec.x / vec.lenght(), vec.y / vec.lenght(), vec.z / vec.lenght()};
}

inline Matrix4 lookAt(const Vector3& eye, const Vector3& target, const Vector3& worldUp) {
    Vector3 forward = (target - eye).normalize(); 
    Vector3 right = cross(forward, worldUp).normalize();  
    Vector3 up = cross(right, forward).normalize();
    Matrix4 result(1.f);

    result.matrix[0][0] = right.x;
    result.matrix[1][0] = right.y;
    result.matrix[2][0] = right.z;
    result.matrix[3][0] = -right.dotProduct(eye);

    result.matrix[0][1] = up.x;
    result.matrix[1][1] = up.y;
    result.matrix[2][1] = up.z;
    result.matrix[3][1] = -up.dotProduct(eye);

    result.matrix[0][2] = -forward.x;
    result.matrix[1][2] = -forward.y;
    result.matrix[2][2] = -forward.z;
    result.matrix[3][2] = forward.dotProduct(eye);

    return result;
}

