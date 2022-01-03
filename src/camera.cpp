#include "headers/vec.h"
#include "headers/camera.h"

Camera::Camera() {
	fov_ = 45.0f;
	aspect_ = 16.0f / 9.0f;
	resolution_ = 4.0f;
	num_pixels_y_ = (int)(fov_ * resolution_);
	num_pixels_x_ = (int)(aspect_ * fov_ * resolution_);

	position_ = Vec3(0.0f, 0.0f, 1.0f);
	lookat_ = Vec3(0.0f, 0.0f, -1.0f);
	up_ = Vec3(0.0f, 1.0f, 0.0f);
	right_ = Vec3(1.0f, 0.0f, 0.0f);
}

int Camera::getNumPixelsX() { return num_pixels_x_; }

int Camera::getNumPixelsY() { return num_pixels_y_; }

Ray Camera::pixelToRay(int x_pixel, int y_pixel) {
	float yfov = fov_ * (float)M_PI / 180.0f;
	float xfov = aspect_ * yfov;

	float dtheta_y = yfov / num_pixels_y_;
	float dtheta_x = xfov / num_pixels_x_;

	return Ray(position_,
		lookat_
		+ up_ * -tan(-yfov / 2 + dtheta_y * y_pixel)
		+ right_ * tan(-xfov / 2 + dtheta_x * x_pixel)
	);
}

