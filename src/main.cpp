#include <iostream>

#include "headers/vec.h"
#include "headers/camera.h"


//void printvec(Vec3& v) {
	//std::cout << "<" << v.x << ", " << v.y << ", " << v.z << ">" << std::endl;
//}

int main() {
	Camera cam = Camera();
	Ray px2r = cam.pixelToRay(400, 200);
}