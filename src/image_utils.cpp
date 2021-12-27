#include <string>
#include <fstream>
#include "headers/vec.h"
#include "headers/image_utils.h"

ImageBufferPixel::ImageBufferPixel() : r(0), g(0), b(0) {}

ImageBufferPixel::ImageBufferPixel(const Vec3& v) : r((int)v.x), g((int)v.y), b((int)v.z) {}

ImageBufferPixel::ImageBufferPixel(int r, int g, int b) : r(r), g(g), b(b) {}

void ImageBufferPixel::setPixelValues(const Vec3& v) {
	r = (int)v.x; g = (int)v.y; b = (int)v.z;
}

void ImageBufferPixel::setPixelValues(int r, int g, int b) {
	this->r = r; this->g = g; this->b = b;
}

ImageBuffer::ImageBuffer(int num_pixels_x, int num_pixels_y) {
	num_pixels_x_ = num_pixels_x;
	num_pixels_y_ = num_pixels_y;
	pixel_grid_ = new ImageBufferPixel[num_pixels_y_ * num_pixels_x_];
}

ImageBuffer::~ImageBuffer() {
	delete[] pixel_grid_;
}

int ImageBuffer::getNumPixelsX() { return num_pixels_x_; }

int ImageBuffer::getNumPixelsY() { return num_pixels_y_; }


ImageBufferPixel ImageBuffer::getPixel(int x, int y) {
	return pixel_grid_[x + y * num_pixels_x_];
}

void ImageBuffer::setPixel(int x, int y, const Vec3& v) {
	pixel_grid_[x + y * num_pixels_x_].setPixelValues(v);
}

void ImageBuffer::setPixel(int x, int y, int r, int g, int b) {
	pixel_grid_[x + y * num_pixels_x_].setPixelValues(r, g, b);
}

void ImageBuffer::saveToPPM(std::string image_name) {
	std::string file_name = image_name;
	std::string extension = file_name.substr(file_name.length() - 4, file_name.length());
	file_name = (extension == ".ppm") ? file_name : file_name + ".ppm";
	std::ofstream image;
	image.open(file_name);
	image << "P3\n" << num_pixels_x_ << " " << num_pixels_y_ << "\n255\n";
	for (int y = 0; y < num_pixels_y_; y++) {
		for (int x = 0; x < num_pixels_x_; x++) {
			ImageBufferPixel px = getPixel(x, y);
			image << px.r << " " << px.g << " " << px.b << "\n";
		}
	}
	image.close();
}