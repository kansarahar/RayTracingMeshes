#include <vector>
#include <math.h>
#include "headers/vec.h"
#include "headers/geometry.h"

#define _USE_MATH_DEFINES

TriangleGeometry::TriangleGeometry(Vec3f v1, Vec3f v2) {
	// set vertices and faces
	std::vector<Vec3f> vertices;
	std::vector<Vec3i> faces;
	vertices.reserve(3);
	faces.reserve(1);

	vertices.push_back(Vec3f());
	vertices.push_back(v1);
	vertices.push_back(v2);

	faces.push_back(Vec3i(0, 1, 2));

	setVertices(vertices);
	setFaces(faces);

	// calculate vertex normals
	std::vector<Vec3f> vertex_normals;
	vertex_normals.reserve(vertices.size());

	Vec3f normal = (v1.cross(v2)).unit();
	vertex_normals.push_back(normal);
	vertex_normals.push_back(normal);
	vertex_normals.push_back(normal);

	setVertexNormals(vertex_normals);
}

CubeGeometry::CubeGeometry() : CubeGeometry(1.0f) {}

CubeGeometry::CubeGeometry(float side_length) {
	std::vector<Vec3f> vertices;
	std::vector<Vec3i> faces;

	vertices.reserve(8);
	faces.reserve(12);

	float s = side_length / 2;

	vertices.push_back(Vec3f(s, s, s)); // 0
	vertices.push_back(Vec3f(-s, s, s)); // 1
	vertices.push_back(Vec3f(s, -s, s)); // 2
	vertices.push_back(Vec3f(s, s, -s)); // 3
	vertices.push_back(Vec3f(-s, -s, s)); // 4
	vertices.push_back(Vec3f(s, -s, -s)); // 5
	vertices.push_back(Vec3f(-s, s, -s)); // 6
	vertices.push_back(Vec3f(-s, -s, -s)); // 7

	// faces touching vertex 0
	faces.push_back(Vec3i(0, 1, 4));
	faces.push_back(Vec3i(0, 4, 2));
	faces.push_back(Vec3i(0, 2, 5));
	faces.push_back(Vec3i(0, 5, 3));
	faces.push_back(Vec3i(0, 3, 6));
	faces.push_back(Vec3i(0, 6, 1));

	// faces touching vertex 7
	faces.push_back(Vec3i(7, 6, 3));
	faces.push_back(Vec3i(7, 3, 5));
	faces.push_back(Vec3i(7, 5, 2));
	faces.push_back(Vec3i(7, 2, 4));
	faces.push_back(Vec3i(7, 4, 1));
	faces.push_back(Vec3i(7, 1, 6));

	setVertices(vertices);
	setFaces(faces);

	// calculate vertex normals
	std::vector<Vec3f> vertex_normals;
	vertex_normals.reserve(vertices.size());

	for (auto it = vertices.begin(); it != vertices.end(); it++) {
		vertex_normals.push_back(it->unit());
	}

	setVertexNormals(vertex_normals);
}

SphereGeometry::SphereGeometry()
	: SphereGeometry(1, 8, 8) {}

SphereGeometry::SphereGeometry(int horizontal_segments, int vertical_segments)
	: SphereGeometry(1, horizontal_segments, vertical_segments) {}

SphereGeometry::SphereGeometry(float radius, int horizontal_segments, int vertical_segments) {
	std::vector<Vec3f> vertices;
	std::vector<Vec3f> vertex_normals;
	std::vector<Vec3i> faces;
	vertices.reserve(horizontal_segments * (vertical_segments - 1) + 2);
	vertex_normals.reserve(horizontal_segments * (vertical_segments - 1) + 2);
	faces.reserve(2 * horizontal_segments * (vertical_segments - 1));
	float dtheta = (float)M_PI / vertical_segments;
	float dphi = 2 * (float)M_PI / horizontal_segments;
	// generate the vertices not including the poles
	for (int v = 1; v < vertical_segments; v++) {
		for (int h = 0; h < horizontal_segments; h++) {
			Vec3f r = Vec3f(
				sin(dtheta * v) * cos(dphi * h),
				cos(dtheta * v),
				-sin(dtheta * v) * sin(dphi * h)
			);
			vertices.push_back(r * radius);
			vertex_normals.push_back(r);
		}
	}
	// generate the faces of the triangles not connected to the poles
	for (int v = 1; v < vertical_segments - 1; v++) {
		for (int h = 0; h < horizontal_segments; h++) {
			int mod_h_1 = (h + 1 < horizontal_segments) ? h + 1 : 0;
			// lower triangle of square face
			faces.push_back(Vec3i(
				(v - 1) * horizontal_segments + h,
				v * horizontal_segments + h,
				v * horizontal_segments + mod_h_1
			));
			// upper triangle of square face
			faces.push_back(Vec3i(
				(v - 1) * horizontal_segments + h,
				v * horizontal_segments + mod_h_1,
				(v - 1) * horizontal_segments + mod_h_1
			));
		}
	}
	// generate the vertices and faces of the triangles of the poles
	vertices.push_back(Vec3f(0, radius, 0));
	vertex_normals.push_back(Vec3f(0, 1, 0));
	vertices.push_back(Vec3f(0, -radius, 0));
	vertex_normals.push_back(Vec3f(0, -1, 0));
	for (int h = 0; h < horizontal_segments; h++) {
		int mod_h_1 = (h + 1 < horizontal_segments) ? h + 1 : 0;
		// triangles attached to north pole
		faces.push_back(Vec3i((int)vertices.size() - 2, h, mod_h_1));
		// triangles attached to south pole
		faces.push_back(Vec3i(
			(int)vertices.size() - 1,
			(vertical_segments - 2) * horizontal_segments + mod_h_1,
			(vertical_segments - 2) * horizontal_segments + h
		));
	}

	setVertices(vertices);
	setVertexNormals(vertex_normals);
	setFaces(faces);
}

PlaneGeometry::PlaneGeometry()
	: PlaneGeometry(1) {}

PlaneGeometry::PlaneGeometry(float side_length) {
	std::vector<Vec3f> vertices;
	std::vector<Vec3f> vertex_normals;
	std::vector<Vec3i> faces;

	vertices.reserve(4);
	vertex_normals.reserve(4);
	faces.reserve(2);

	float s = side_length / 2;
	vertices.push_back(Vec3f(s, s, 0));
	vertices.push_back(Vec3f(-s, s, 0));
	vertices.push_back(Vec3f(s, -s, 0));
	vertices.push_back(Vec3f(-s, -s, 0));
	
	vertex_normals.push_back(Vec3f(0, 0, 1));
	vertex_normals.push_back(Vec3f(0, 0, 1));
	vertex_normals.push_back(Vec3f(0, 0, 1));
	vertex_normals.push_back(Vec3f(0, 0, 1));

	faces.push_back(Vec3i(0, 1, 2));
	faces.push_back(Vec3i(3, 2, 1));

	setVertices(vertices);
	setVertexNormals(vertex_normals);
	setFaces(faces);
}