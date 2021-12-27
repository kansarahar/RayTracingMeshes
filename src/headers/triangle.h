#pragma once

#include "vec.h"
#include "object3D.h"

class Triangle : public Object3D {
public:
	Triangle();
	Triangle(Vec3 vertex0, Vec3 vertex1, Vec3 vertex2);
	~Triangle();

	float intersect(Ray& r) override;

private:
	Vec3 calculateCenter();

	Vec3 v0_, v1_, v2_;
	Vec3 normal_;
};