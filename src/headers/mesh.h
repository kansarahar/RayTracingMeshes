#pragma once

#include <vector>
#include "vec.h"
#include "geometry.h"

class BoundingSphere {
public:
	BoundingSphere();
	BoundingSphere(Vec3f center, float radius);
	Vec3f center;
	float radius;
	bool intersect(Ray& r);
};

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
	void calculate_bounding_sphere_();

	std::vector<Vec3f> vertices_;
	std::vector<Vec3f> vertex_normals_;
	std::vector<Vec3i> faces_;

	bool use_vertex_normals_;
	Vec3f position_;
	Mat4f transformations_;
	BoundingSphere bounding_sphere_;
};




// vertex normals will transform via:
// https://en.wikipedia.org/wiki/Cross_product#Algebraic_properties
// https://mathworld.wolfram.com/MatrixInverse.html