#include <iostream>
#include <string>
#include <vector>

#include "headers/vec.h"
#include "headers/camera.h"
#include "headers/image_utils.h"
#include "headers/object3D.h"
#include "headers/triangle.h"

//void printvec(Vec3& v) {
	//std::cout << "<" << v.x << ", " << v.y << ", " << v.z << ">" << std::endl;
//}

int main() {
	Camera cam = Camera();

	unsigned xpx = cam.getNumPixelsX();
	unsigned ypx = cam.getNumPixelsY();

	//ImageBuffer i = ImageBuffer(2, 2);
	//i.setPixel(1, 1, Vec3(255, 0, 0));
	//i.setPixel(1, 2, Vec3(0, 255, 0));
	//i.saveToPPM("test.ppm");


	Triangle t = Triangle();
	ImageBuffer i = ImageBuffer(xpx, ypx);

	for (unsigned y = 0; y < ypx; y++) {
		for (unsigned x = 0; x < xpx; x++) {
			Ray r = cam.pixelToRay(x, y);
			if (t.intersect(r) > 0) {
				i.setPixel(x, y, Vec3(255, 0, 0));
			}
		}
	}
	i.saveToPPM("test.ppm");
	Ray r2 = cam.pixelToRay(xpx / 2, ypx / 2);
	float b = t.intersect(r2);
}