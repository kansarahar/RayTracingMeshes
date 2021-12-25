#include "headers/camera.h"

Camera::Camera() : 
	_fov(45.0f), _aspect(2), _ypixels(200), _xpixels((int)(_aspect * _ypixels)),
	_position(Vec3(0.0f, 0.0f, 1.0f)), _lookat(Vec3(0.0f, 0.0f, -1.0f)), _up(Vec3(0.0f, 1.0f, 0.0f)), _right(Vec3(1.0f, 0.0f, 0.0f)
) {}

Ray Camera::pixelToRay(unsigned xpixel, unsigned ypixel) {
	float yfov = _fov * (float)M_PI / 180.0f;
	float xfov = _aspect * _fov * (float)M_PI / 180.0f;

	float dthetaY = yfov / _ypixels;
	float dthetaX = xfov / _xpixels;

	return Ray(_position, Vec3(tan(-xfov / 2 + dthetaY * xpixel), tan(-yfov / 2 + dthetaY * ypixel), -1));
}