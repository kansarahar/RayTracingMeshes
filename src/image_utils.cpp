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

int ImageBuffer::getNumPixelsX() const { return num_pixels_x_; }

int ImageBuffer::getNumPixelsY() const { return num_pixels_y_; }


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

	std::cout << "Saving image as " << file_name << std::endl;

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

	std::cout << "Saving image as " << file_name << std::endl;
}

#pragma pack(push, 1)
struct BitmapHeader {
	// Bitmap File Header
	uint16_t file_type = 0x4D42;
	uint32_t file_size = 0;
	uint32_t reserved_bits = 0;
	uint32_t offset_bits = 54;

	// Bitmap Info Header
	uint32_t info_size = 40;
	uint32_t width = 0;
	uint32_t height = 0;
	uint16_t planes = 1;
	uint16_t bits_per_px = 24;
	uint32_t compression = 0;
	uint32_t image_size = 0;
	uint32_t x_px_per_m = 0;
	uint32_t y_px_per_m = 0;
	uint32_t colors_used = 0;
	uint32_t important_colors = 0;
};
#pragma pack(pop)

void ImageBuffer::saveToBMP(std::string image_name) {
	std::string file_name = image_name;
	std::string extension = file_name.substr(file_name.length() - 4, file_name.length());
	file_name = (extension == ".bmp") ? file_name : file_name + ".bmp";

	const uint32_t width = getNumPixelsX();
	const uint32_t height = getNumPixelsY();

	const uint32_t header_size = 54;
	const uint32_t padding = width % 4 == 0 ? 0 : 4 - (3 * width % 4);
	const uint32_t content_size = 3 * (width + padding) * height;

	std::cout << "Saving image as " << file_name << std::endl;

	std::ofstream image(image_name, std::ios::out | std::ios::binary);
	
	BitmapHeader bh;
	bh.file_size = (uint32_t)(header_size + content_size);
	bh.width = width;
	bh.height = height;

	// write header
	char header[header_size];
	memcpy(header, &bh, header_size);
	image.write(header, header_size);

	// write content
	for (int y = num_pixels_y_ - 1; y >= 0; y--) {
		// row of pixels
		for (int x = 0; x < num_pixels_x_; x++) {
			ImageBufferPixel px = getPixel(x, y);
			const char r = px.r;
			const char g = px.g;
			const char b = px.b;
			image.write(&b, 1);
			image.write(&g, 1);
			image.write(&r, 1);
		}
		// padding for the row
		image.write(NULL, padding);
	}
	image.close();

	std::cout << "Image saved as " << file_name << std::endl;
}
