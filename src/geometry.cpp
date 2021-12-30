#include <vector>
#include <math.h>
#include "headers/vec.h"
#include "headers/geometry.h"

#define _USE_MATH_DEFINES

TriangleGeometry::TriangleGeometry(Vec3 v1, Vec3 v2) {
	// set vertices and faces
	std::vector<Vec3> vertices;
	std::vector<Face> faces;
	vertices.reserve(3);
	faces.reserve(1);

	vertices.push_back(Vec3());
	vertices.push_back(v1);
	vertices.push_back(v2);

	faces.push_back(Face(0, 1, 2));

	setVertices(vertices);
	setFaces(faces);

	// calculate vertex normals
	std::vector<Vec3> vertex_normals;
	vertex_normals.reserve(vertices.size());

	Vec3 normal = (v1.cross(v2)).unit();
	vertex_normals.push_back(normal);
	vertex_normals.push_back(normal);
	vertex_normals.push_back(normal);

	setVertexNormals(vertex_normals);
}

//CubeGeometry::CubeGeometry() : CubeGeometry(1.0f) {}
//
//CubeGeometry::CubeGeometry(float side_length) {
//
//}

//SphereGeometry::SphereGeometry() {}
//
//void SphereGeometry::constructGeometry(float radius, int horizontal_segments, int vertical_segments) {
//	std::vector<Vec3> vertices;
//	std::vector<Face> faces;
//	vertices.reserve(horizontal_segments * (vertical_segments - 1) + 2);
//	faces.reserve(2 * horizontal_segments * (vertical_segments - 1));
//	float dtheta = M_PI / vertical_segments;
//	float dphi = 2 * M_PI / horizontal_segments;
//	// generate the vertices and faces of the triangles not attached to the poles
//	for (int v = 1; v < vertical_segments-1; v++) {
//		for (int h = 0; h < horizontal_segments; h++) {
//			int mod_h_1 = (h + 1 < horizontal_segments) ? h + 1 : 0;
//			vertices.push_back(Vec3(sin(dtheta * v) * cos(dphi * h), cos(dtheta * v), -sin(dtheta * v) * sin(dphi * h)) * radius);
//			faces.push_back(Face(
//				(v - 1) * horizontal_segments + h,
//				v * horizontal_segments + h,
//				v * horizontal_segments + mod_h_1
//			)); // lower triangle of square face
//			faces.push_back(Face(
//				(v - 1) * horizontal_segments + h,
//				v * horizontal_segments + mod_h_1,
//				(v - 1) * horizontal_segments + mod_h_1
//			)); // upper triangle of square face
//		}
//	}
//	// generate the vertices and faces of the triangles of the poles
//	vertices.push_back(Vec3(0, radius, 0));
//	vertices.push_back(Vec3(0, -radius, 0));
//	for (int h = 0; h < horizontal_segments; h++) {
//		int mod_h_1 = (h + 1 < horizontal_segments) ? h + 1 : 0;
//		faces.push_back(Face(vertices.size() - 2, h, mod_h_1)); // triangles attached to north pole
//		faces.push_back(Face(
//			vertices.size() - 1,
//			(vertical_segments - 2) * horizontal_segments + mod_h_1,
//			(vertical_segments - 2) * horizontal_segments + h
//		)); // triangles attached to south pole
//	}