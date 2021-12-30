#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>

class Vec3 {
public:
	// constructors
	Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	// simple operations
	float dot(const Vec3& other) const { return x * other.x + y * other.y + z * other.z; }
	Vec3 cross(const Vec3& other) const { return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }
	
	float norm() const { return sqrt(this->dot(*this)); }
	float norm2() const { return this->dot(*this); }

	Vec3 unit() const { return *this / this->norm(); }

	// overloaded operators
	Vec3 operator * (const float& c) const { return Vec3(x * c, y * c, z * c); }
	Vec3 operator / (const float& c) const { return Vec3(x / c, y / c, z / c); }

	Vec3 operator + (const Vec3& other) const { return Vec3(x + other.x, y + other.y, z + other.z); }
	Vec3 operator - (const Vec3& other) const { return Vec3(x - other.x, y - other.y, z - other.z); }
	Vec3 operator * (const Vec3& other) const { return Vec3(x * other.x, y * other.y, z * other.z); }

	Vec3& operator *= (const float& c) { x *= c, y *= c, z *= c; return *this; }
	Vec3& operator /= (const float& c) { x /= c, y /= c, z /= c; return *this; }

	Vec3& operator += (const Vec3& other) { x += other.x, y += other.y, z += other.z; return *this; }
	Vec3& operator -= (const Vec3& other) { x -= other.x, y -= other.y, z -= other.z; return *this; }
	Vec3& operator *= (const Vec3& other) { x *= other.x, y *= other.y, z *= other.z; return *this; }

	float& operator [] (int i) { return (&x)[i]; }
	const float& operator [] (int i) const { return (&x)[i]; }

	// member variables
	float x, y, z;
};

class Ray {
public:
	// constructors
	Ray() : origin(Vec3()), direction(Vec3(0.0f, 0.0f, -1.0f)) {}
	Ray(Vec3 origin, Vec3 direction) : origin(origin), direction(direction.unit()) {}

	// simple operations
	Vec3 at(const float& t) const { return origin + direction * t; }

	// member variables
	Vec3 origin, direction;
};

class Mat4 {
public:
	// constructors
	Mat4() {}
	Mat4(float c) {
		matrix[0][0] = c;
		matrix[1][1] = c;
		matrix[2][2] = c;
	}
	Mat4(
		float a, float b, float c, float d,
		float e, float f, float g, float h,
		float i, float j, float k, float l,
		float m, float n, float o, float p
	) {
		matrix[0][0] = a; matrix[0][1] = b; matrix[0][2] = c; matrix[0][3] = d;
		matrix[1][0] = e; matrix[1][1] = f; matrix[1][2] = g; matrix[1][3] = h;
		matrix[2][0] = i; matrix[2][1] = j; matrix[2][2] = k; matrix[2][3] = l;
		matrix[3][0] = m; matrix[3][1] = n; matrix[3][2] = o; matrix[3][3] = p;
	}

	// simple operations
	Mat4 transpose() const {
		Mat4 result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.matrix[i][j] = matrix[j][i];
			}
		}
	}

	// overloaded operators
	Vec3 operator * (const Vec3& v) const {
		Vec3 result;
		for (int i = 0; i < 3; i++) {
			result[i] = matrix[i][0] * v[0] + matrix[i][1] * v[1] + matrix[i][2] * v[2] + matrix[i][3];
		}
		return result;
	}
	Mat4 operator * (const Mat4& other) const {
		Mat4 result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.matrix[i][j] = 0;
				for (int k = 0; k < 4; k++) {
					result.matrix[i][j] += matrix[i][k] * other[k][j];
				}
			}
		}
		return result;
	}

	float* operator [] (int i) { return matrix[i]; }
	const float* operator [] (int i) const { return matrix[i]; }

	// member variables
	float matrix[4][4]{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
};
