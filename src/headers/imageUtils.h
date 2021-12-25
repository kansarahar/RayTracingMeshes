#pragma once

class ImageBuffer {
public:
	unsigned pxWidth, pxHeight;
	unsigned* pixelGrid;

	ImageBuffer(const unsigned pxWidth, const unsigned pxHeight);
	~ImageBuffer();


};
