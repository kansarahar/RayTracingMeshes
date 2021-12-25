#pragma once

#include "vec.h"

class Object3D {
public:
	Vec3 center;
	float radius;

	Object3D();
	Object3D(Vec3 center, float radius);

};