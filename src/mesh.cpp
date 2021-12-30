#include "headers/vec.h"
#include "headers/geometry.h"
#include "headers/mesh.h"

#define __INTERSECTION_TOLERANCE__ 0.000001f
#define __BACKFACE_CULLING__ true

Mesh::Mesh(Geometry& g) {
	vertices_ = g.getVertices();
	vertex_normals_ = g.getVertexNormals();

	faces_ = g.getFaces();
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

	return true;
}

bool Mesh::intersect_helper_(Face& face, Ray& r) {
	Vec3& v0 = vertices_[face.v0];
	Vec3& v1 = vertices_[face.v1];
	Vec3& v2 = vertices_[face.v2];

	Vec3 normal = ((v1 - v0).cross(v2 - v0)).unit();

	float nd = normal.dot(r.direction);
#if __BACKFACE_CULLING__
	if (-nd < __INTERSECTION_TOLERANCE__) { return false; }
#else
	if (abs(nd) < __INTERSECTION_TOLERANCE__) { return false; }
#endif
	float t = normal.dot(v0 - r.origin) / nd;
	Vec3 p = r.at(t);
	float u = normal.dot((v0 - v2).cross(p - v2));
	float v = normal.dot((v1 - v0).cross(p - v0));
	float w = normal.dot((v2 - v1).cross(p - v2));
	if (u > 0 && v > 0 && w > 0) {
		return true;
	}
	return false;
}

bool Mesh::intersect(Ray& r) {
	for (int face_idx = 0; face_idx < faces_.size(); face_idx++) {
		Face face = faces_[face_idx];
		return mt_intersect_helper_(face, r);
	}
	return false;
}
