#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <limits>

template <typename T>
class Vec2 {
public:
	// constructors
	Vec2<T>() : x(T(0)), y(T(0)) {}
	Vec2<T>(T x, T y) : x(x), y(y) {}

	// simple operations
	T dot(const Vec2<T>& other) const { return x * other.x + y * other.y; }
	
	T norm() const { return sqrt(this->dot(*this)); }
	T norm2() const { return this->dot(*this); }
	Vec2<T> unit() const { return *this / this->norm(); }

	// overloaded operators
	Vec2<T> operator * (const float& c) const { return Vec2<T>(x * c, y * c); }
	Vec2<T> operator / (const float& c) const { return Vec2<T>(x / c, y / c); }

	Vec2<T> operator + (const Vec2<T>& other) const { return Vec2<T>(x + other.x, y + other.y); }
	Vec2<T> operator - (const Vec2<T>& other) const { return Vec2<T>(x - other.x, y - other.y); }
	Vec2<T> operator * (const Vec2<T>& other) const { return Vec2<T>(x * other.x, y * other.y); }

	Vec2<T>& operator *= (const T& c) { x *= c, y *= c; return *this; }
	Vec2<T>& operator /= (const T& c) { x /= c, y /= c; return *this; }

	Vec2<T>& operator += (const Vec2<T>& other) { x += other.x, y += other.y; return *this; }
	Vec2<T>& operator -= (const Vec2<T>& other) { x -= other.x, y -= other.y; return *this; }
	Vec2<T>& operator *= (const Vec2<T>& other) { x *= other.x, y *= other.y; return *this; }

	T& operator [] (int i) { return (&x)[i]; }
	const T& operator [] (int i) const { return (&x)[i]; }

	// member variables
	T x, y;
};
typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;

template <typename T>
class Vec3 {
public:
	// constructors
	Vec3<T>() : x(T(0)), y(T(0)), z(T(0)) {}
	Vec3<T>(T x, T y, T z) : x(x), y(y), z(z) {}

	// simple operations
	T dot(const Vec3<T>& other) const { return x * other.x + y * other.y + z * other.z; }
	Vec3<T> cross(const Vec3<T>& other) const { return Vec3<T>(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }
	
	T norm() const { return sqrt(this->dot(*this)); }
	T norm2() const { return this->dot(*this); }

	Vec3<T> unit() const { return *this / this->norm(); }

	// overloaded operators
	Vec3<T> operator * (const T& c) const { return Vec3<T>(x * c, y * c, z * c); }
	Vec3<T> operator / (const T& c) const { return Vec3<T>(x / c, y / c, z / c); }

	Vec3<T> operator + (const Vec3<T>& other) const { return Vec3<T>(x + other.x, y + other.y, z + other.z); }
	Vec3<T> operator - (const Vec3<T>& other) const { return Vec3<T>(x - other.x, y - other.y, z - other.z); }
	Vec3<T> operator * (const Vec3<T>& other) const { return Vec3<T>(x * other.x, y * other.y, z * other.z); }

	Vec3<T>& operator *= (const T& c) { x *= c, y *= c, z *= c; return *this; }
	Vec3<T>& operator /= (const T& c) { x /= c, y /= c, z /= c; return *this; }

	Vec3<T>& operator += (const Vec3<T>& other) { x += other.x, y += other.y, z += other.z; return *this; }
	Vec3<T>& operator -= (const Vec3<T>& other) { x -= other.x, y -= other.y, z -= other.z; return *this; }
	Vec3<T>& operator *= (const Vec3<T>& other) { x *= other.x, y *= other.y, z *= other.z; return *this; }

	T& operator [] (int i) { return (&x)[i]; }
	const T& operator [] (int i) const { return (&x)[i]; }

	// member variables
	T x, y, z;
};
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

class Mat4f {
public:
	// constructors
	Mat4f() {}
	Mat4f(float c) {
		matrix[0][0] = c;
		matrix[1][1] = c;
		matrix[2][2] = c;
	}
	Mat4f(Vec3f v) {
		matrix[0][0] = v.x;
		matrix[1][1] = v.y;
		matrix[2][2] = v.z;
	}
	Mat4f(
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
	Mat4f transpose() const {
		Mat4f result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.matrix[i][j] = matrix[j][i];
			}
		}
		return result;
	}

	// overloaded operators
	Vec3f operator * (const Vec3f& v) const {
		Vec3f result;
		for (int i = 0; i < 3; i++) {
			result[i] = matrix[i][0] * v[0] + matrix[i][1] * v[1] + matrix[i][2] * v[2] + matrix[i][3];
		}
		return result;
	}
	Mat4f operator * (const Mat4f& other) const {
		Mat4f result;
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

class Mesh;
struct IntersectInfo {
	Mesh* nearest_mesh;
	Vec3i* face;
	Vec3f normal;
	float t;

	IntersectInfo()
		: nearest_mesh(nullptr), face(nullptr), normal(Vec3f()), t(std::numeric_limits<float>::max()) {}
};

class Ray {
public:
	// constructors
	Ray() : origin(Vec3f()), direction(Vec3f(0.0f, 0.0f, -1.0f)), intersect_info(IntersectInfo()) {}
	Ray(Vec3f origin, Vec3f direction) : origin(origin), direction(direction.unit()), intersect_info(IntersectInfo()) {}

	// simple operations
	Vec3f at(const float& t) const { return origin + direction * t; }

	// member variables
	Vec3f origin, direction;
	IntersectInfo intersect_info;
};
