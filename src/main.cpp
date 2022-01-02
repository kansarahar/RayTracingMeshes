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

	Camera* c = new Camera();
	Scene* s = new Scene();
	Light* l = new Light(Vec3(1,-1,-1), Vec3(255,255,255), 0.9f);
	s->add(l);

	//TriangleGeometry tg1 = TriangleGeometry(Vec3(0.5f, 0.0f, 0.0f), Vec3(0.0f, 0.5f, 0.0f));
	//TriangleGeometry tg2 = TriangleGeometry(Vec3(0.25f, 0.10f, 0.25f), Vec3(-0.1f, 0.25f, -0.25f));
	//Mesh* triangleMesh1 = new Mesh(tg1);
	//Mesh* triangleMesh2 = new Mesh(tg2);
	//s->add(triangleMesh1);
	//s->add(triangleMesh2);
	//triangleMesh1->color = Vec3(255, 0, 0);
	//triangleMesh2->color = Vec3(0, 255, 0);

	CubeGeometry c1 = CubeGeometry(0.5f);
	Mesh* cubeMesh = new Mesh(c1);
	s->add(cubeMesh);
	//cubeMesh->color = Vec3(0, 0, 255);

	Renderer renderer = Renderer(s, c);
	renderer.render();
	//renderer.saveToPPM("test.ppm");
	renderer.saveToBMP("test.bmp");

	//Timer timer = Timer();
	//Vec3 v = Vec3();
	//for (int i = 0; i < 10000000; i++) {
	//	v.x += 0.002f + v.y;
	//	v.y += v.x * -1 + 0.001f;
	//	Vec3 v2 = Vec3();
	//	v += v2;
	//}
}
