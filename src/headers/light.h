#pragma once

#include "vec.h"

enum class LightType { directional, point, area };

class Light {
public:
	Vec3 getLuminosity() { return color_ * intensity_; }
	LightType type;
protected:
	void setColor(Vec3 color) { color_ = color / 255; }
	void setIntensity(float intensity) { intensity_ = intensity; }
private:
	Vec3 color_;
	float intensity_;
};

class DirectionalLight : public Light {
public:
	DirectionalLight(Vec3 direction, Vec3 color, float intensity) {
		type = LightType::directional;
		direction_ = direction;
		setColor(color);
		setIntensity(intensity);
	}
	Vec3 getDirection() { return direction_; }
private:
	void setDirection(Vec3 direction) { direction_ = direction.unit(); }
	Vec3 direction_;
};

class PointLight : public Light {
public:
	PointLight(Vec3 position, Vec3 color, float intensity) {
		type = LightType::point;
		position_ = position;
		setColor(color);
		setIntensity(intensity);
	}
	Vec3 getPosition() { return position_; }
private:
	Vec3 position_;
};

class AreaLight : public Light {
public:
	AreaLight(Vec3 position, Vec3 axis1, Vec3 axis2, Vec3 color, float intensity) {
		type = LightType::area;
		position_ = position;
		axis1_ = axis1;
		axis2_ = axis2;
		setColor(color);
		setIntensity(intensity);
	}
private:
	Vec3 position_;
	Vec3 axis1_;
	Vec3 axis2_;
};
