#pragma once

#include <vector>

#include "mesh.h"
#include "light.h"

class Scene {
public:
	std::vector<Mesh*> meshes;
	std::vector <Light*> lights;
	void add(Mesh* m) { meshes.push_back(m); }
	void add(Light* l) { lights.push_back(l); }
	Vec3f getBackgroundColor() { return Vec3f(0x87,0xCE,0xEB); }
};