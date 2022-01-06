#pragma once

#include <string>
#include "vec.h"

class ImageBuffer {
public:

	ImageBuffer(int num_pixels_x, int num_pixels_y);
	~ImageBuffer();

	int getNumPixelsX() const;
	int getNumPixelsY() const;

	Vec3i& getPixel(int x, int y) const;
	void setPixel(int x, int y, const Vec3f& v);
	void setPixel(int x, int y, int r, int g, int b);
	
	void saveToPPM(std::string image_name);
	void saveToBMP(std::string image_name);

private:
	int num_pixels_x_, num_pixels_y_;
	Vec3i* pixel_grid_;
};
