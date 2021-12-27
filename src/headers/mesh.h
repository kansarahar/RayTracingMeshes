#pragma once

#include "object3D.h"

class Mesh : public Object3D {
public:
	Mesh();
	virtual float intersect(Ray& r) = 0;
};




// vertex normals will transform via:
// https://en.wikipedia.org/wiki/Cross_product#Algebraic_properties
// https://mathworld.wolfram.com/MatrixInverse.html