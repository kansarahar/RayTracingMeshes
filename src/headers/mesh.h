#pragma once

#include <vector>
#include "vec.h"
#include "geometry.h"



class Mesh {
public:
	Mesh(Geometry& g);
	bool intersect(Ray& r);
private:
	bool mt_intersect_helper_(Face& face, Ray& r);
	bool intersect_helper_(Face& face, Ray& r);

	std::vector<Vec3> vertices_;
	std::vector<Face> faces_;

	std::vector<Vec3> vertex_normals_;

	//Vec3 center_;
	//Mat4 transformations_;
};




// vertex normals will transform via:
// https://en.wikipedia.org/wiki/Cross_product#Algebraic_properties
// https://mathworld.wolfram.com/MatrixInverse.html