#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include "headers/vec.h"
#include "headers/renderer.h"
#include "headers/camera.h"
#include "headers/scene.h"
#include "headers/image_utils.h"
#include "headers/geometry.h"
#include "headers/mesh.h"

class Timer {
public:
	std::chrono::time_point<std::chrono::steady_clock> start, end;

	Timer() {
		start = std::chrono::steady_clock::now();
	}

	~Timer() {
		end = std::chrono::steady_clock::now();
		std::chrono::duration<float> duration = end - start;

		float ms = duration.count() * 1000.0f;
		std::cout << "Time elapsed: " << ms << "ms" << std::endl;
	}
};

int main() {

	Camera* c = new Camera(45, 16.0f / 9.0f, 4);
	Scene* s = new Scene();
	Light* dl = new DirectionalLight(Vec3f(0.5,-1,-1), Vec3f(255,255,255), 0.9f);
	Light* pl = new PointLight(Vec3f(-1.5, 2, 2), Vec3f(255, 255, 255), 0.9f);
	Light* al = new AreaLight(Vec3f(-1.5, 3, 3), Vec3f(2, 0, 1), Vec3f(0, 1, 0), Vec3f(250,250,250), 0.9f);
	s->add(al);

	//TriangleGeometry tg1 = TriangleGeometry(Vec3(0.5f, 0.0f, 0.0f), Vec3(0.0f, 0.5f, 0.0f));
	//TriangleGeometry tg2 = TriangleGeometry(Vec3(0.25f, 0.10f, 0.25f), Vec3(-0.1f, 0.25f, -0.25f));
	//Mesh* triangleMesh1 = new Mesh(tg1);
	//Mesh* triangleMesh2 = new Mesh(tg2);
	//s->add(triangleMesh1);
	//s->add(triangleMesh2);
	//triangleMesh1->color = Vec3(255, 0, 0);
	//triangleMesh2->color = Vec3(0, 255, 0);

	//CubeGeometry c1 = CubeGeometry(0.5f);
	//Mesh* cubeMesh = new Mesh(c1);
	//s->add(cubeMesh);
	//cubeMesh->useVertexNormals();
	//cubeMesh->color = Vec3(0, 0, 255);
	//cubeMesh->rotateSelfX(30);
	//cubeMesh->rotateSelfY(30);
	//cubeMesh->translate(Vec3(0.25, 0.25, -2));
	//cubeMesh->applyTransformations();

	//c->translate(Vec3(0.1, 0, 0));
	//c->rotateSelfY(-5);
	PlaneGeometry pg = PlaneGeometry(1);
	SphereGeometry sg = SphereGeometry(0.25, 10,10);
	Mesh* planeMesh = new Mesh(pg);
	Mesh* sphereMesh = new Mesh(sg);
	s->add(planeMesh);
	s->add(sphereMesh);
	planeMesh->color = Vec3f(255,255,255);
	sphereMesh->useVertexNormals();
	planeMesh->rotateSelfX(-30);
	planeMesh->rotateSelfY(-30);
	planeMesh->translate(Vec3f(0.25, -0.5, -1.5));
	sphereMesh->translate(Vec3f(0, 0, -1));
	sphereMesh->rotateSelfX(1);

	Renderer renderer = Renderer(s, c);
	renderer.render();
	//renderer.saveToPPM("test.ppm");
	renderer.saveToBMP("test.bmp");
}
