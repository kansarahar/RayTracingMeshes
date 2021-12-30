#pragma once

#include <string>

#include "vec.h"
#include "camera.h"
#include "scene.h"
#include "image_utils.h"

class Renderer {
public:
	Renderer(Scene* scene, Camera* camera);
	~Renderer();

	void render();
	void saveToPPM(std::string image_name);
private:
	bool trace_(Ray& r);

	ImageBuffer* image_buffer_;
	Scene* scene_;
	Camera* camera_;
};