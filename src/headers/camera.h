#pragma once

#include "vec.h"

class Camera {
public:
	Camera();
	
	unsigned getNumPixelsX();
	unsigned getNumPixelsY();

	Ray pixelToRay(unsigned xpixel, unsigned ypixel);

private:
	float fov_;
	float aspect_;
	int ypixels_;
	int xpixels_;

	Vec3 position_;
	Vec3 lookat_;
	Vec3 up_;
	Vec3 right_;
};