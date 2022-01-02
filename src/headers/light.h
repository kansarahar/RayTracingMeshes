#pragma once

#include "vec.h"

class Light {
public:
	Light(Vec3 direction, Vec3 color, float intensity)
		: direction_(direction.unit()), color_(color / 255), intensity_(intensity) {}
	Vec3 getIntensity() { return color_ * intensity_; }
	Vec3 getDirection() { return direction_; }
protected:
	void setDirection(Vec3 direction) { direction_ = direction.unit(); }
	void setColor(Vec3 color) { color_ = color / 255; }
	void setIntensity(float intensity) { intensity_ = intensity; }
private:
	Vec3 direction_;
	Vec3 color_;
	float intensity_;
};
