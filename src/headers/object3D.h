#pragma once

#include "vec.h"

class Object3D {
public:
	virtual float intersect(Ray& r) = 0;
	
	virtual Vec3 getCenter() { return center_; }
	virtual void setCenter(Vec3 center) { center_ = center; }

	//virtual Vec3 getNormal(Ray& r) = 0;
	//virtual void transform(Mat4& m) { transformations_ *= m; }
	//virtual void applyTransformations() = 0;

private:
	Vec3 center_ = Vec3(0,0,0);
	Mat4 transformations_ = Mat4();
};