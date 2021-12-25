#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>

class Vec3 {
public:
	float x, y, z;

	// constructors
	Vec3() : x(0), y(0), z(0) {}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	// simple vector operations
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

	float& operator [] (unsigned i) { return (&x)[i]; }

};

class Ray {
public:
	Vec3 origin, direction;

	Ray() : origin(Vec3()), direction(Vec3(0.0f, 0.0f, -1.0f)) {}
	Ray(Vec3 origin, Vec3 direction) : origin(origin), direction(direction.unit()) {}

	Vec3 at(const float& t) const { return origin + direction * t; }
};

class Mat4 {
public:
	float matrix[4][4];

	Mat4() {
		for (unsigned i = 0; i < 4; i++) {
			for (unsigned j = 0; j < 4; j++) { matrix[i][j] = (i != j) ? 0.0f : 1.0f; }
		}
	};

	Mat4(float c) {
		for (unsigned i = 0; i < 4; i++) {
			for (unsigned j = 0; j < 4; j++) { matrix[i][j] = (i != j) ? 0.0f : c; }
		}
		matrix[3][3] = 1;
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
	};

	Mat4 transpose() const {
		Mat4 result = Mat4();
		for (unsigned i = 0; i < 4; i++) {
			for (unsigned j = 0; j < 4; j++) { result.matrix[i][j] = matrix[j][i]; }
		}
	}

	Vec3 operator * (const Vec3& v) const {
		Vec3 result = Vec3();
		for (unsigned i = 0; i < 3; i++) {
			result[i] = matrix[i][0] * v.x + matrix[i][1] * v.y + matrix[i][2] * v.z + matrix[i][3];
		}
		return result;
	}
	Mat4 operator * (const Mat4& other) const {
		Mat4 result = Mat4();
		for (unsigned i = 0; i < 4; i++) {
			for (unsigned j = 0; j < 4; j++) {
				result.matrix[i][j] = 0;
				for (unsigned k = 0; k < 4; k++) {
					result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
				}
			}
		}
		return result;
	}
	Mat4& operator *= (const Mat4& other) {
		Mat4 result = *this * other;
		for (unsigned i = 0; i < 4; i++) {
			for (unsigned j = 0; j < 4; j++) { matrix[i][j] = result.matrix[i][j]; }
		}
		return *this;
	}

};