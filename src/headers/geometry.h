#pragma once

#include <vector>
#include "vec.h"

// base class, will be used to construct meshes
class Geometry {
public:
	std::vector<Vec3f> getVertices() { return vertices_; }
	std::vector<Vec3f> getVertexNormals() { return vertex_normals_; }
	std::vector<Vec3i> getFaces() { return faces_; }

protected:
	//virtual void constructGeometry() = 0;
	void setVertices(std::vector<Vec3f> vertices) { vertices_ = vertices; }
	void setVertexNormals(std::vector<Vec3f> vertex_normals) { vertex_normals_ = vertex_normals; }
	void setFaces(std::vector<Vec3i> faces) { faces_ = faces; }

private:
	std::vector<Vec3f> vertices_;
	std::vector<Vec3f> vertex_normals_;
	std::vector<Vec3i> faces_;
};

class TriangleGeometry : public Geometry {
public:
	TriangleGeometry(Vec3f v1, Vec3f v2);
};

class CubeGeometry : public Geometry {
public:
	CubeGeometry();
	CubeGeometry(float side_length);
};

class SphereGeometry : public Geometry {
public:
	SphereGeometry();
	SphereGeometry(int horizontal_segments, int vertical_segments);
	SphereGeometry(float radius, int horizontal_segments, int vertical_segments);
};

class PlaneGeometry : public Geometry {
public:
	PlaneGeometry();
	PlaneGeometry(float side_length);
};