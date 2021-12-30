#include "headers/vec.h"
#include "headers/geometry.h"
#include "headers/mesh.h"

#define __INTERSECTION_TOLERANCE__ 0.000001f
#define __BACKFACE_CULLING__ false

Mesh::Mesh(Geometry& g) {
	vertices_ = g.getVertices();
	faces_ = g.getFaces();
	vertex_normals_ = g.getVertexNormals();
}

float Mesh::mt_intersect_helper_(Ray& r, Face& face) {
	// implementation of the Moller-Trumbore algorithm
	Vec3& v0 = vertices_[face.v0];
	Vec3& v1 = vertices_[face.v1];
	Vec3& v2 = vertices_[face.v2];

	Vec3 l1 = v1 - v0;
	Vec3 l2 = v2 - v0;
	Vec3 normal = l1.cross(l2);
	float det = -r.direction.dot(normal);
#ifdef __BACKFACE_CULLING__
	if (det < __INTERSECTION_TOLERANCE__) { return -1; }
#else
	if (abs(det) < __INTERSECTION_TOLERANCE__) { return -1; }
#endif
	Vec3 q = r.origin - v0;
	Vec3 dxq = r.direction.cross(q);

	float u = -l2.dot(dxq) / det;
	if (u < 0 || u > 1) { return -1; }
	float v = l1.dot(dxq) / det;
	if (v < 0 || u + v > 1) { return -1; }
	float t = q.dot(normal);

	return t;
}

float Mesh::intersect_helper_(Ray& r, Face& face) {
	Vec3& v0 = vertices_[face.v0];
	Vec3& v1 = vertices_[face.v1];
	Vec3& v2 = vertices_[face.v2];

	Vec3 normal = (v1 - v0).cross(v2 - v0);

	float nd = normal.dot(r.direction);
	if (abs(nd) < __INTERSECTION_TOLERANCE__) {
		return -1;
	}
	float t = normal.dot(v0 - r.origin) / nd;
	Vec3 p = r.at(t);
	if (
		normal.dot((v1 - v0).cross(p - v0)) > 0
		&& normal.dot((v2 - v1).cross(p - v1)) > 0
		&& normal.dot((v0 - v2).cross(p - v2)) > 0
	) {
		return t;
	}
	return -1;
}

float Mesh::intersect(Ray& r) {
	for (int face_idx = 0; face_idx < faces_.size(); face_idx++) {
		Face face = faces_[face_idx];
		float t = mt_intersect_helper_(r, face);
		if (t > 0) return t;
	}
	return -1;
}
