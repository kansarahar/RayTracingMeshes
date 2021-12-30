#include "headers/vec.h"
#include "headers/camera.h"

Camera::Camera() : 
	fov_(45.0f), aspect_(2), ypixels_(400), xpixels_((int)(aspect_* ypixels_)),
	position_(Vec3(0.0f, 0.0f, 1.0f)), lookat_(Vec3(0.0f, 0.0f, -1.0f)), up_(Vec3(0.0f, 1.0f, 0.0f)), right_(Vec3(1.0f, 0.0f, 0.0f)
) {}

int Camera::getNumPixelsX() { return xpixels_; }

int Camera::getNumPixelsY() { return ypixels_; }

Ray Camera::pixelToRay(int xpixel, int ypixel) {
	float yfov = fov_ * (float)M_PI / 180.0f;
	float xfov = aspect_ * fov_ * (float)M_PI / 180.0f;

	float dthetaY = yfov / ypixels_;
	float dthetaX = xfov / xpixels_;

	return Ray(position_, Vec3(tan(-xfov / 2 + dthetaY * xpixel), -tan(-yfov / 2 + dthetaY * ypixel), -1));
}

