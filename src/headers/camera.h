#pragma once

#include "vec.h"

class Camera {
public:
	Camera();
	Camera(float fov, float aspect, float resolution);
	
	int getNumPixelsX();
	int getNumPixelsY();

	void translate(Vec3f v);
	void rotateSelfX(float degrees);
	void rotateSelfY(float degrees);
	void rotateSelfZ(float degrees);

	Ray pixelToRay(int xpixel, int ypixel);

private:
	float fov_;
	float aspect_;
	float resolution_;
	int num_pixels_y_;
	int num_pixels_x_;

	Vec3f position_;
	Vec3f lookat_;
	Vec3f up_;
	Vec3f right_;

};
