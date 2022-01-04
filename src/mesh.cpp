#include "headers/vec.h"
#include "headers/geometry.h"
#include "headers/mesh.h"

#define __INTERSECTION_TOLERANCE__ 0.000001f
#define __BACKFACE_CULLING__ true

Mesh::Mesh(Geometry& g) {
	vertices_ = g.getVertices();
	vertex_normals_ = g.getVertexNormals();

	faces_ = g.getFaces();

	use_vertex_normals_ = false;
	position_ = Vec3();
	transformations_ = Mat4();

	color = Vec3(255, 0, 0);
}

Vec3 Mesh::getPosition() {
	return position_;
}

void Mesh::useVertexNormals() { use_vertex_normals_ = true; }

bool Mesh::intersect(Ray& r) {
	bool hit = false;
	for (int face_idx = 0; face_idx < faces_.size(); face_idx++) {
		Face& face = faces_[face_idx];
		hit = mt_intersect_helper_(face, r) || hit;
	}
	return hit;
}

void Mesh::translate(Vec3 v) {
	Mat4 translation_matrix = Mat4();
	translation_matrix[0][3] = v.x;
	translation_matrix[1][3] = v.y;
	translation_matrix[2][3] = v.z;

	position_ = translation_matrix * position_;
	transformations_ = translation_matrix * transformations_;
}

void Mesh::rotateSelfX(float degrees) {
	float theta = degrees * (float)M_PI / 180;
	Mat4 rotation_matrix = Mat4();
	rotation_matrix[1][1] = cos(theta);
	rotation_matrix[1][2] = -sin(theta);
	rotation_matrix[2][2] = cos(theta);
	rotation_matrix[2][1] = sin(theta);

	Vec3 curr_position = position_;
	translate(curr_position * -1);
	transformations_ = rotation_matrix * transformations_;
	translate(curr_position);
}

void Mesh::rotateSelfY(float degrees) {
	float theta = degrees * (float)M_PI / 180;
	Mat4 rotation_matrix = Mat4();
	rotation_matrix[0][0] = cos(theta);
	rotation_matrix[0][2] = sin(theta);
	rotation_matrix[2][0] = -sin(theta);
	rotation_matrix[2][2] = cos(theta);

	Vec3 curr_position = position_;
	translate(curr_position * -1);
	transformations_ = rotation_matrix * transformations_;
	translate(curr_position);
}

void Mesh::rotateSelfZ(float degrees) {
	float theta = degrees * (float)M_PI / 180;
	Mat4 rotation_matrix = Mat4();
	rotation_matrix[0][0] = cos(theta);
	rotation_matrix[0][1] = -sin(theta);
	rotation_matrix[1][0] = sin(theta);
	rotation_matrix[1][1] = cos(theta);

	Vec3 curr_position = position_;
	translate(curr_position * -1);
	transformations_ = rotation_matrix * transformations_;
	translate(curr_position);
}

void Mesh::applyTransformations() {
	for (auto it = vertices_.begin(); it != vertices_.end(); it++) {
		(*it) = transformations_ * (*it);
	}

	// transform vertex normals
	Mat4 vn_transformations = Mat4();
	Mat4& t_ = transformations_;
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
	for (auto it = vertex_normals_.begin(); it != vertex_normals_.end(); it++) {
		(*it) = (vn_transformations * (*it)).unit();
	}
}

bool Mesh::mt_intersect_helper_(Face& face, Ray& r) {
	// implementation of the Moller-Trumbore algorithm
	Vec3& v0 = vertices_[face.v0];
	Vec3& v1 = vertices_[face.v1];
	Vec3& v2 = vertices_[face.v2];

	Vec3 l1 = v1 - v0;
	Vec3 l2 = v2 - v0;
	Vec3 normal = l1.cross(l2);
	float det = -r.direction.dot(normal);
#if __BACKFACE_CULLING__
	if (det < __INTERSECTION_TOLERANCE__) { return false; }
#else
	if (abs(det) < __INTERSECTION_TOLERANCE__) { return false; }
#endif
	Vec3 q = r.origin - v0;
	Vec3 dxq = r.direction.cross(q);

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
			: vertex_normals_[face.v0] * (1 - u - v) + vertex_normals_[face.v1] * u + vertex_normals_[face.v2] * v;
		r.intersect_info.t = t * (1 - __INTERSECTION_TOLERANCE__);
	}
	return true;
}

