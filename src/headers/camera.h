#pragma once

#include "vec.h"

class Camera {
public:
	Camera();
	
	int getNumPixelsX();
	int getNumPixelsY();

	Ray pixelToRay(int xpixel, int ypixel);

private:
	float fov_;
	float aspect_;
	float resolution_;
	int num_pixels_y_;
	int num_pixels_x_;

	Vec3 position_;
	Vec3 lookat_;
	Vec3 up_;
	Vec3 right_;
};