#pragma once

#include "vec.h"

enum class LightType { directional, point, area };

class Light {
public:
	Vec3f getLuminosity() { return color_ * intensity_; }
	virtual LightType getType() = 0;
protected:
	void setColor(Vec3f color) { color_ = color / 255; }
	void setIntensity(float intensity) { intensity_ = intensity; }
private:
	Vec3f color_;
	float intensity_ = 0;
};

class DirectionalLight : public Light {
public:
	DirectionalLight(Vec3f direction, Vec3f color, float intensity) {
		direction_ = direction;
		setColor(color);
		setIntensity(intensity);
	}
	LightType getType() override { return LightType::directional; }
	Vec3f getDirection() { return direction_; }
private:
	void setDirection(Vec3f direction) { direction_ = direction.unit(); }
	Vec3f direction_;
};

class PointLight : public Light {
public:
	PointLight(Vec3f position, Vec3f color, float intensity) {
		position_ = position;
		setColor(color);
		setIntensity(intensity);
	}
	LightType getType() override { return LightType::point; }
	Vec3f getPosition() { return position_; }
private:
	Vec3f position_;
};

class AreaLight : public Light {
public:
	AreaLight(Vec3f position, Vec3f axis1, Vec3f axis2, Vec3f color, float intensity) {
		position_ = position;
		axis1_ = axis1;
		axis2_ = axis2;
		setColor(color);
		setIntensity(intensity);
	}
	LightType getType() override { return LightType::area; }
	Vec3f getPosition() { return position_; }
	Vec3f getAxis1() { return axis1_; }
	Vec3f getAxis2() { return axis2_; }
private:
	Vec3f position_;
	Vec3f axis1_;
	Vec3f axis2_;
};
