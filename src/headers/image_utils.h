#pragma once

#include <string>
#include "vec.h"

class ImageBufferPixel {
public:
	unsigned r, g, b;

	ImageBufferPixel();
	ImageBufferPixel(const Vec3& v);
	ImageBufferPixel(unsigned r, unsigned g, unsigned b);

	void setPixelValues(const Vec3& v);
	void setPixelValues(unsigned r, unsigned g, unsigned b);
};

class ImageBuffer {
public:

	ImageBuffer(unsigned num_pixels_x, unsigned num_pixels_y);
	~ImageBuffer();

	unsigned getNumPixelsX();
	unsigned getNumPixelsY();

	ImageBufferPixel getPixel(unsigned x, unsigned y);
	void setPixel(unsigned x, unsigned y, const Vec3& v);
	void setPixel(unsigned x, unsigned y, unsigned r, unsigned g, unsigned b);
	
	void saveToPPM(std::string image_name);

private:
	unsigned num_pixels_x_, num_pixels_y_;
	ImageBufferPixel* pixel_grid_;
};