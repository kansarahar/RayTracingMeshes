#include "headers/imageUtils.h"

ImageBuffer::ImageBuffer(unsigned pxWidth, unsigned pxHeight) {
	this->pxWidth = pxWidth;
	this->pxHeight = pxHeight;
	this->pixelGrid = new unsigned[pxHeight * pxWidth * 3];
}

ImageBuffer::~ImageBuffer() {
	delete[] pixelGrid;
}