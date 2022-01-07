#include <math.h>

#include "headers/vec.h"
#include "headers/geometry.h"
#include "headers/mesh.h"

#define __INTERSECTION_TOLERANCE__ 0.000001f
#define __BACKFACE_CULLING__ true

BoundingSphere::BoundingSphere()
	: BoundingSphere(Vec3f(), 1) {}

BoundingSphere::BoundingSphere(Vec3f center, float radius)
	: center(center), radius(radius) {}

bool BoundingSphere::intersect(Ray& r) {
	float a = r.direction.dot(r.direction);
	Vec3f oc = r.origin - center;
	float b = 2 * r.direction.dot(oc);
	float c = oc.dot(oc) - radius * radius;
	float disc = b * b - 4 * a * c;
	if (disc < 0) { return false; }
	float t = (-b - sqrt(disc)) / 2 * a;
	if (t < 0) {
		t = (-b + sqrt(disc)) / 2 * a;
	}
	return t > 0;
}

Mesh::Mesh(Geometry& g) {
	vertices_ = g.getVertices();
	vertex_normals_ = g.getVertexNormals();

	faces_ = g.getFaces();

	use_vertex_normals_ = false;
	position_ = Vec3f();
	transformations_ = Mat4f();

	calculate_bounding_sphere_();

	color = Vec3f(255, 0, 0);
}

Vec3f Mesh::getPosition() {
	return position_;
}

void Mesh::useVertexNormals() { use_vertex_normals_ = true; }

bool Mesh::intersect(Ray& r) {
	if (!bounding_sphere_.intersect(r)) { return false; }
	bool hit = false;
	for (Vec3i& face : faces_) {
		hit = mt_intersect_helper_(face, r) || hit;
	}
	return hit;
}

void Mesh::translate(Vec3f v) {
	Mat4f translation_matrix = Mat4f();
	translation_matrix[0][3] = v.x;
	translation_matrix[1][3] = v.y;
	translation_matrix[2][3] = v.z;

	position_ = translation_matrix * position_;
	transformations_ = translation_matrix * transformations_;
}

void Mesh::rotateSelfX(float degrees) {
	float theta = degrees * (float)M_PI / 180;
	Mat4f rotation_matrix = Mat4f();
	rotation_matrix[1][1] = cos(theta);
	rotation_matrix[1][2] = -sin(theta);
	rotation_matrix[2][2] = cos(theta);
	rotation_matrix[2][1] = sin(theta);

	Vec3f curr_position = position_;
	translate(curr_position * -1);
	transformations_ = rotation_matrix * transformations_;
	translate(curr_position);
}

void Mesh::rotateSelfY(float degrees) {
	float theta = degrees * (float)M_PI / 180;
	Mat4f rotation_matrix = Mat4f();
	rotation_matrix[0][0] = cos(theta);
	rotation_matrix[0][2] = sin(theta);
	rotation_matrix[2][0] = -sin(theta);
	rotation_matrix[2][2] = cos(theta);

	Vec3f curr_position = position_;
	translate(curr_position * -1);
	transformations_ = rotation_matrix * transformations_;
	translate(curr_position);
}

void Mesh::rotateSelfZ(float degrees) {
	float theta = degrees * (float)M_PI / 180;
	Mat4f rotation_matrix = Mat4f();
	rotation_matrix[0][0] = cos(theta);
	rotation_matrix[0][1] = -sin(theta);
	rotation_matrix[1][0] = sin(theta);
	rotation_matrix[1][1] = cos(theta);

	Vec3f curr_position = position_;
	translate(curr_position * -1);
	transformations_ = rotation_matrix * transformations_;
	translate(curr_position);
}

void Mesh::applyTransformations() {
	for (Vec3f& vertex : vertices_) {
		vertex = transformations_ * vertex;
	}

	// transform vertex normals
	Mat4f vn_transformations = Mat4f();
	Mat4f& t_ = transformations_;
	vn_transformations[0][0] = t_[2][2] * t_[3][3] - t_[2][3] * t_[3][2];
	vn_transformations[0][1] = t_[1][3] * t_[3][2] - t_[1][2] * t_[3][3];
	vn_transformations[0][2] = t_[1][2] * t_[2][3] - t_[1][3] * t_[2][2];

	vn_transformations[1][0] = t_[2][3] * t_[3][1] - t_[2][1] * t_[3][3];
	vn_transformations[1][1] = t_[1][1] * t_[3][3] - t_[1][3] * t_[3][1];
	vn_transformations[1][2] = t_[1][3] * t_[2][1] - t_[1][1] * t_[2][3];

	vn_transformations[2][0] = t_[2][1] * t_[3][2] - t_[2][2] * t_[3][1];
	vn_transformations[2][1] = t_[1][2] * t_[3][1] - t_[1][1] * t_[3][2];
	vn_transformations[2][2] = t_[1][1] * t_[2][2] - t_[1][2] * t_[2][1];

	vn_transformations = vn_transformations.transpose();
	for (Vec3f& vertex_normal : vertex_normals_) {
		vertex_normal = (vn_transformations * vertex_normal).unit();
	}

	calculate_bounding_sphere_();
}

bool Mesh::mt_intersect_helper_(Vec3i& face, Ray& r) {
	// implementation of the Moller-Trumbore algorithm
	Vec3f& v0 = vertices_[face.x];
	Vec3f& v1 = vertices_[face.y];
	Vec3f& v2 = vertices_[face.z];

	Vec3f l1 = v1 - v0;
	Vec3f l2 = v2 - v0;
	Vec3f normal = l1.cross(l2);
	float det = -r.direction.dot(normal);
#if __BACKFACE_CULLING__
	if (det < __INTERSECTION_TOLERANCE__) { return false; }
#else
	if (abs(det) < __INTERSECTION_TOLERANCE__) { return false; }
#endif
	Vec3f q = r.origin - v0;
	Vec3f dxq = r.direction.cross(q);

	float u = -l2.dot(dxq) / det;
	if (u < 0 || u > 1) { return false; }
	float v = l1.dot(dxq) / det;
	if (v < 0 || u + v > 1) { return false; }
	float t = q.dot(normal) / det;
	if (t < 0) { return false; }

	if (r.intersect_info.t > t) {
		r.intersect_info.nearest_mesh = this;
		r.intersect_info.face = &face;
		r.intersect_info.normal = !use_vertex_normals_ ? normal.unit()
			: vertex_normals_[face.x] * (1 - u - v) + vertex_normals_[face.y] * u + vertex_normals_[face.z] * v;
		r.intersect_info.t = t * (1 - __INTERSECTION_TOLERANCE__);
	}
	return true;
}

void Mesh::calculate_bounding_sphere_() {
	float r2max = 0;
	for (Vec3f& vertex : vertices_) {
		float dist2 = (position_ - vertex).dot(position_ - vertex);
		r2max = r2max > dist2 ? r2max : dist2;
	}
	bounding_sphere_ = BoundingSphere(position_, sqrt(r2max) + __INTERSECTION_TOLERANCE__);
}

