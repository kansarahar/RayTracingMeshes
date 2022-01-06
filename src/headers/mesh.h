#pragma once

#include <vector>
#include "vec.h"
#include "geometry.h"



class Mesh {
public:
	Mesh(Geometry& g);
	Vec3f getPosition();
	void useVertexNormals();

	bool intersect(Ray& r);

	// transformations
	void translate(Vec3f v);
	void rotateSelfX(float degrees);
	void rotateSelfY(float degrees);
	void rotateSelfZ(float degrees);
	void applyTransformations();


	Vec3f color;
private:
	bool mt_intersect_helper_(Vec3i& face, Ray& r);

	std::vector<Vec3f> vertices_;
	std::vector<Vec3f> vertex_normals_;
	std::vector<Vec3i> faces_;

	bool use_vertex_normals_;
	Vec3f position_;
	Mat4f transformations_;
};




// vertex normals will transform via:
// https://en.wikipedia.org/wiki/Cross_product#Algebraic_properties
// https://mathworld.wolfram.com/MatrixInverse.html