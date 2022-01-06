#include "headers/vec.h"
#include "headers/camera.h"

Camera::Camera() {
	fov_ = 45.0f;
	aspect_ = 16.0f / 9.0f;
	resolution_ = 4.0f;
	num_pixels_y_ = (int)(fov_ * resolution_);
	num_pixels_x_ = (int)(aspect_ * fov_ * resolution_);

	position_ = Vec3f(0.0f, 0.0f, 1.0f);
	lookat_ = Vec3f(0.0f, 0.0f, -1.0f);
	up_ = Vec3f(0.0f, 1.0f, 0.0f);
	right_ = Vec3f(1.0f, 0.0f, 0.0f);
}

Camera::Camera(float fov, float aspect, float resolution) {
	fov_ = fov;
	aspect_ = aspect;
	resolution_ = resolution;
	num_pixels_y_ = (int)(fov_ * resolution_);
	num_pixels_x_ = (int)(aspect_ * fov_ * resolution_);

	position_ = Vec3f(0.0f, 0.0f, 1.0f);
	lookat_ = Vec3f(0.0f, 0.0f, -1.0f);
	up_ = Vec3f(0.0f, 1.0f, 0.0f);
	right_ = Vec3f(1.0f, 0.0f, 0.0f);
}

int Camera::getNumPixelsX() { return num_pixels_x_; }

int Camera::getNumPixelsY() { return num_pixels_y_; }


void Camera::translate(Vec3f v) {
	Mat4f translation_matrix = Mat4f();
	translation_matrix[0][3] = v.x;
	translation_matrix[1][3] = v.y;
	translation_matrix[2][3] = v.z;

	position_ = translation_matrix * position_;
}

void Camera::rotateSelfX(float degrees) {
	float theta = degrees * (float)M_PI / 180;
	Mat4f rotation_matrix = Mat4f();
	rotation_matrix[1][1] = cos(theta);
	rotation_matrix[1][2] = -sin(theta);
	rotation_matrix[2][2] = cos(theta);
	rotation_matrix[2][1] = sin(theta);

	lookat_ = rotation_matrix * lookat_;
	up_ = rotation_matrix * up_;
	right_ = rotation_matrix * right_;
}

void Camera::rotateSelfY(float degrees) {
	float theta = degrees * (float)M_PI / 180;
	Mat4f rotation_matrix = Mat4f();
	rotation_matrix[0][0] = cos(theta);
	rotation_matrix[0][2] = sin(theta);
	rotation_matrix[2][0] = -sin(theta);
	rotation_matrix[2][2] = cos(theta);

	lookat_ = rotation_matrix * lookat_;
	up_ = rotation_matrix * up_;
	right_ = rotation_matrix * right_;
}

void Camera::rotateSelfZ(float degrees) {
	float theta = degrees * (float)M_PI / 180;
	Mat4f rotation_matrix = Mat4f();
	rotation_matrix[0][0] = cos(theta);
	rotation_matrix[0][1] = -sin(theta);
	rotation_matrix[1][0] = sin(theta);
	rotation_matrix[1][1] = cos(theta);

	lookat_ = rotation_matrix * lookat_;
	up_ = rotation_matrix * up_;
	right_ = rotation_matrix * right_;
}

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
