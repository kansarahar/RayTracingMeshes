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

bool Renderer::trace_(Ray& r) {
	bool hit = false;
	for (int mesh_ptr_idx = 0; mesh_ptr_idx < scene_->meshes.size(); mesh_ptr_idx++) {
		Mesh* mesh = scene_->meshes[mesh_ptr_idx];
		hit = mesh->intersect(r) || hit;
	}
	return hit;
}

void Renderer::render() {
	for (int y = 0; y < camera_->getNumPixelsY(); y++) {
		for (int x = 0; x < camera_->getNumPixelsX(); x++) {
			Ray r = camera_->pixelToRay(x, y);
			if (trace_(r)) {
				image_buffer_->setPixel(x, y, r.intersect_info.mesh->color);
			}
		}
	}
}

void Renderer::saveToPPM(std::string image_name) {
	image_buffer_->saveToPPM(image_name);
}