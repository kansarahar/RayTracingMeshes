#include <iostream>
#include <string>
#include <vector>

#include "headers/vec.h"
#include "headers/renderer.h"
#include "headers/camera.h"
#include "headers/scene.h"
#include "headers/image_utils.h"
#include "headers/geometry.h"
#include "headers/mesh.h"



int main() {

	Camera* c = new Camera();
	Scene* s = new Scene();

	TriangleGeometry tg1 = TriangleGeometry(Vec3(0.5f, 0.0f, 0.0f), Vec3(0.0f, 0.5f, 0.0f));
	TriangleGeometry tg2 = TriangleGeometry(Vec3(0.25f, -0.25f, -0.05f), Vec3(0.25f, 0.25f, 0.01f));
	Mesh* triangleMesh1 = new Mesh(tg1);
	Mesh* triangleMesh2 = new Mesh(tg2);
	s->add(triangleMesh1);
	s->add(triangleMesh2);
	triangleMesh1->color = Vec3(255, 0, 0);
	triangleMesh2->color = Vec3(0, 255, 0);

	
	Renderer renderer = Renderer(s, c);
	renderer.render();
	renderer.saveToPPM("testRender.ppm");
}