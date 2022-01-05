#pragma once

#include "vec.h"

enum class LightType { directional, point, area };

class Light {
public:
	Vec3 getLuminosity() { return color_ * intensity_; }
	virtual LightType getType() = 0;
protected:
	void setColor(Vec3 color) { color_ = color / 255; }
	void setIntensity(float intensity) { intensity_ = intensity; }
private:
	Vec3 color_;
	float intensity_ = 0;
};

class DirectionalLight : public Light {
public:
	DirectionalLight(Vec3 direction, Vec3 color, float intensity) {
		direction_ = direction;
		setColor(color);
		setIntensity(intensity);
	}
	LightType getType() override { return LightType::directional; }
	Vec3 getDirection() { return direction_; }
private:
	void setDirection(Vec3 direction) { direction_ = direction.unit(); }
	Vec3 direction_;
};

class PointLight : public Light {
public:
	PointLight(Vec3 position, Vec3 color, float intensity) {
		position_ = position;
		setColor(color);
		setIntensity(intensity);
	}
	LightType getType() override { return LightType::point; }
	Vec3 getPosition() { return position_; }
private:
	Vec3 position_;
};

class AreaLight : public Light {
public:
	AreaLight(Vec3 position, Vec3 axis1, Vec3 axis2, Vec3 color, float intensity) {
		position_ = position;
		axis1_ = axis1;
		axis2_ = axis2;
		setColor(color);
		setIntensity(intensity);
	}
	LightType getType() override { return LightType::area; }
	Vec3 getPosition() { return position_; }
	Vec3 getAxis1() { return axis1_; }
	Vec3 getAxis2() { return axis2_; }
private:
	Vec3 position_;
	Vec3 axis1_;
	Vec3 axis2_;
};
