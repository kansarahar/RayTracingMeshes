#pragma once

#include <vector>
#include "vec.h"

// simple struct that holds the array position of its vertices
struct Face {
	int v0;
	int v1;
	int v2;

	Face(int v0, int v1, int v2) : v0(v0), v1(v1), v2(v2) {}
};

// base class, will be used to construct meshes
class Geometry {
public:
	std::vector<Vec3> getVertices() { return vertices_; }
	std::vector<Face> getFaces() { return faces_; }
	std::vector<Vec3> getVertexNormals() { return vertex_normals_; }

protected:
	//virtual void constructGeometry() = 0;
	void setVertices(std::vector<Vec3> vertices) { vertices_ = vertices; }
	void setFaces(std::vector<Face> faces) { faces_ = faces; }

	void setVertexNormals(std::vector<Vec3> vertex_normals) { vertex_normals_ = vertex_normals; }

private:
	std::vector<Vec3> vertices_;
	std::vector<Vec3> vertex_normals_;
	std::vector<Face> faces_;
};

class TriangleGeometry : public Geometry {
public:
	TriangleGeometry(Vec3 v1, Vec3 v2);
};

//class CubeGeometry: public Geometry {
//public:
//	CubeGeometry();
//	CubeGeometry(float side_length);
//};

//class SphereGeometry : public Geometry {
//public:
//	SphereGeometry();
//	SphereGeometry(int horizontal_segments, int vertical_segments);
//	SphereGeometry(float radius, int horizontal_segments, int vertical_segments);
//protected:
//	void constructGeometry() override;
//	void constructGeometry(float radius, int horizontal_segments, int vertical_segments);
//};