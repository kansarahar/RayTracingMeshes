#include <string>
#include <algorithm>

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
	for (auto it = scene_->meshes.begin(); it != scene_->meshes.end(); ++it) {
		Mesh* mesh = *it;
		hit = mesh->intersect(r) || hit;
	}
	return hit;
}

Vec3 Renderer::castRay_(Ray& r, Light& l) {
	if (trace_(r)) {
		Vec3 light_intensity = l.getIntensity();
		Vec3 light_direction = l.getDirection();
		Vec3 shadow_ray_origin = r.at(r.intersect_info.t);
		Ray shadow_ray = Ray(shadow_ray_origin, light_direction * -1);

		if (trace_(shadow_ray)) {
			return Vec3(0, 0, 0);
		}

		return (r.intersect_info.nearest_mesh->color * light_intensity) * std::max(0.0f, (r.intersect_info.normal.dot(shadow_ray.direction)));
	}
	return scene_->getBackgroundColor();
}

void Renderer::render() {
	for (int y = 0; y < camera_->getNumPixelsY(); y++) {
		for (int x = 0; x < camera_->getNumPixelsX(); x++) {
			Ray r = camera_->pixelToRay(x, y);
			Vec3 px_color = Vec3();
			for (auto it = scene_->lights.begin(); it != scene_->lights.end(); ++it) {
				Light* l = *it;
				px_color += castRay_(r, *l);
			}
			image_buffer_->setPixel(x, y, px_color);
		}
	}
}

void Renderer::saveToPPM(std::string image_name) {
	image_buffer_->saveToPPM(image_name);
}

void Renderer::saveToBMP(std::string image_name) {
	image_buffer_->saveToBMP(image_name);
}
