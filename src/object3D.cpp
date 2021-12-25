#include "headers/object3D.h"

Object3D::Object3D() : center(Vec3(0,0,-3)), radius(1.0f) {}

Object3D::Object3D(Vec3 center, float radius) : center(center), radius(radius) {}

