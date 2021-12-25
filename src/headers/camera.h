#pragma once

#include "vec.h"

class Camera {
public:

	Camera();
	
	Ray pixelToRay(unsigned xpixel, unsigned ypixel);

	float _fov;
	float _aspect;
	int _ypixels;
	int _xpixels;

	Vec3 _position;
	Vec3 _lookat;
	Vec3 _up;
	Vec3 _right;
};