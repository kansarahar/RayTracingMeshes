#include "headers/triangle.h"
#include "headers/object3D.h"

Triangle::Triangle() {
	v0_ = Vec3(-0.5f, -0.5f, -1);
	v1_ = Vec3(-0, 0.5f, -1);
	v2_ = Vec3(0.5f, -0.5f, -1);
	normal_ = ((v1_ - v0_).cross(v2_ - v0_)).unit();
	setCenter(calculateCenter());
}

Triangle::Triangle(Vec3 vertex0, Vec3 vertex1, Vec3 vertex2) {
	v0_ = vertex0;
	v1_ = vertex1;
	v2_ = vertex2;
	normal_ = ((v1_ - v0_).cross(v2_ - v0_)).unit();
	setCenter(calculateCenter());
}

Triangle::~Triangle() {}

float Triangle::intersect(Ray& r) {
	float nd = normal_.dot(r.direction);
	if (nd == 0) { return -1; }
	float t = normal_.dot(v0_-r.origin)/nd;
	Vec3 p = r.at(t);
	if (
		normal_.dot((v1_-v0_).cross(p-v0_)) > 0
		&& normal_.dot((v2_ - v1_).cross(p - v1_)) > 0
		&& normal_.dot((v0_ - v2_).cross(p - v2_)) > 0
	) {
		return t;
	}
	return -1;
}

Vec3 Triangle::calculateCenter() {
	float max_x = std::max(v0_.x, std::max(v1_.x, v2_.x));
	float max_y = std::max(v0_.y, std::max(v1_.y, v2_.y));
	float max_z = std::max(v0_.z, std::max(v1_.z, v2_.z));
	float min_x = std::min(v0_.x, std::min(v1_.x, v2_.x));
	float min_y = std::min(v0_.y, std::min(v1_.y, v2_.y));
	float min_z = std::min(v0_.z, std::min(v1_.z, v2_.z));
	return Vec3((max_x + min_x) / 2, (max_y + min_y) / 2, (max_z + min_z) / 2);
}