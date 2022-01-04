#pragma once

#include <vector>
#include "vec.h"
#include "geometry.h"



class Mesh {
public:
	Mesh(Geometry& g);
	Vec3 getPosition();
	void useVertexNormals();

	bool intersect(Ray& r);

	// transformations
	void translate(Vec3 v);
	void rotateSelfX(float degrees);
	void rotateSelfY(float degrees);
	void rotateSelfZ(float degrees);
	void applyTransformations();


	Vec3 color;
private:
	bool mt_intersect_helper_(Face& face, Ray& r);

	std::vector<Vec3> vertices_;
	std::vector<Face> faces_;

	std::vector<Vec3> vertex_normals_;

	bool use_vertex_normals_;
	Vec3 position_;
	Mat4 transformations_;
};




// vertex normals will transform via:
// https://en.wikipedia.org/wiki/Cross_product#Algebraic_properties
// https://mathworld.wolfram.com/MatrixInverse.html