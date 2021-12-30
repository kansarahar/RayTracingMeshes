#include <string>

#include "headers/vec.h"
#include "headers/camera.h"
#include "headers/scene.h"
#include "headers/image_utils.h"
#include "headers/renderer.h"


Renderer::Renderer(Scene* scene, Camera* camera) {
	scene_ = scene;
	camera_ = camera;
	image_buffer_ = new ImageBuffer(camera->getNumPixelsX(), camera->getNumPixelsY());
}

Renderer::~Renderer() {
	delete image_buffer_;
}

float Renderer::trace_(Ray& r) {
	for (int mesh_ptr_idx = 0; mesh_ptr_idx < scene_->meshes.size(); mesh_ptr_idx++) {
		Mesh& mesh = scene_->meshes[mesh_ptr_idx];
		float t = mesh.intersect(r);
		if (t > 0) { return t; }
	}
	return -1;
}

void Renderer::render() {
	for (int y = 0; y < camera_->getNumPixelsY(); y++) {
		for (int x = 0; x < camera_->getNumPixelsX(); x++) {
			Ray r = camera_->pixelToRay(x, y);
			if (trace_(r) > 0) {
				image_buffer_->setPixel(x, y, Vec3(255, 0, 0));
			}
		}
	}
}

void Renderer::saveToPPM(std::string image_name) {
	image_buffer_->saveToPPM(image_name);
}