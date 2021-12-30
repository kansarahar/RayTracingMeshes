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

	TriangleGeometry tg = TriangleGeometry(Vec3(0.5f, 0.0f, 0.0f), Vec3(0.0f, 0.5f, 0.0f));
	Mesh* triangleMesh = new Mesh(tg);
	s->add(triangleMesh);
	
	Renderer renderer = Renderer(s, c);
	renderer.render();
	renderer.saveToPPM("testRender.ppm");
}