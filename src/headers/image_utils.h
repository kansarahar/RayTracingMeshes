#pragma once

#include <string>
#include "vec.h"

class ImageBufferPixel {
public:
	int r, g, b;

	ImageBufferPixel();
	ImageBufferPixel(const Vec3& v);
	ImageBufferPixel(int r, int g, int b);

	void setPixelValues(const Vec3& v);
	void setPixelValues(int r, int g, int b);
};

class ImageBuffer {
public:

	ImageBuffer(int num_pixels_x, int num_pixels_y);
	~ImageBuffer();

	int getNumPixelsX();
	int getNumPixelsY();

	ImageBufferPixel getPixel(int x, int y);
	void setPixel(int x, int y, const Vec3& v);
	void setPixel(int x, int y, int r, int g, int b);
	
	void saveToPPM(std::string image_name);

private:
	int num_pixels_x_, num_pixels_y_;
	ImageBufferPixel* pixel_grid_;
};