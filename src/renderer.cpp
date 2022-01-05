#include <string>
#include <algorithm>
#include <stdlib.h>

#include "headers/vec.h"
#include "headers/camera.h"
#include "headers/scene.h"
#include "headers/image_utils.h"
#include "headers/renderer.h"

#define __NUM_CELLS_PER_ROW__ 8

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
		if (l.getType() == LightType::directional) {
			DirectionalLight& dl = (DirectionalLight&)l;
			Vec3 light_luminosity = dl.getLuminosity();
			Vec3 light_direction = dl.getDirection();
			Ray shadow_ray = Ray(r.at(r.intersect_info.t), light_direction * -1);

			if (trace_(shadow_ray)
				&& !(shadow_ray.intersect_info.nearest_mesh == r.intersect_info.nearest_mesh
				&& shadow_ray.intersect_info.face == r.intersect_info.face)
			) {
				return Vec3(0, 0, 0);
			}

			return (r.intersect_info.nearest_mesh->color * light_luminosity) * std::max(0.0f, (r.intersect_info.normal.dot(shadow_ray.direction)));
		}
		if (l.getType() == LightType::point) {
			PointLight& pl = (PointLight&)l;
			Vec3 light_luminosity = pl.getLuminosity();
			Vec3 light_direction = (r.at(r.intersect_info.t) - pl.getPosition()).unit();
			Ray shadow_ray = Ray(r.at(r.intersect_info.t), light_direction * -1);

			if (trace_(shadow_ray)
				&& !(shadow_ray.intersect_info.nearest_mesh == r.intersect_info.nearest_mesh
				&& shadow_ray.intersect_info.face == r.intersect_info.face)
			) {
				return Vec3(0, 0, 0);
			}

			return (r.intersect_info.nearest_mesh->color * light_luminosity) * std::max(0.0f, (r.intersect_info.normal.dot(shadow_ray.direction)));
		}
		if (l.getType() == LightType::area) {
			float random_jitters[__NUM_CELLS_PER_ROW__][__NUM_CELLS_PER_ROW__][2];
			for (int i = 0; i < __NUM_CELLS_PER_ROW__; i++) {
				for (int j = 0; j < __NUM_CELLS_PER_ROW__; j++) { 
					random_jitters[i][j][0] = float(rand() % 100) / 100.0f;
					random_jitters[i][j][1] = float(rand() % 100) / 100.0f;
				}
			}
			AreaLight& al = (AreaLight&)l;
			Vec3 light_luminosity = al.getLuminosity();
			Vec3 axes1 = al.getAxis1();
			Vec3 axes2 = al.getAxis2();
			Vec3 collected_illumination = Vec3();
			for (int i = 0; i < __NUM_CELLS_PER_ROW__; i++) {
				for (int j = 0; j < __NUM_CELLS_PER_ROW__; j++) {
					Vec3 light_direction = (
						r.at(r.intersect_info.t)
						- al.getPosition()
						- al.getAxis1() * (2 * i - __NUM_CELLS_PER_ROW__ + random_jitters[i][j][0]) / __NUM_CELLS_PER_ROW__
						- al.getAxis2() * (2 * j - __NUM_CELLS_PER_ROW__ + random_jitters[i][j][1]) / __NUM_CELLS_PER_ROW__
					).unit();
					Ray shadow_ray = Ray(r.at(r.intersect_info.t), light_direction * -1);

					if (trace_(shadow_ray)
						&& !(shadow_ray.intersect_info.nearest_mesh == r.intersect_info.nearest_mesh
						&& shadow_ray.intersect_info.face == r.intersect_info.face)
					) {
						continue;
					}
					collected_illumination += (r.intersect_info.nearest_mesh->color * light_luminosity) * std::max(0.0f, (r.intersect_info.normal.dot(shadow_ray.direction)));
				}
			}
			return collected_illumination / __NUM_CELLS_PER_ROW__ / __NUM_CELLS_PER_ROW__;
		}
	}
	return scene_->getBackgroundColor();
}

void Renderer::render() {
	// apply transformations to all meshes before rendering image
	for (auto it = scene_->meshes.begin(); it != scene_->meshes.end(); it++) {
		(*it)->applyTransformations();
	}
	// render image
	for (int y = 0; y < camera_->getNumPixelsY(); y++) {
		for (int x = 0; x < camera_->getNumPixelsX(); x++) {
			Ray r = camera_->pixelToRay(x, y);
			Vec3 px_color = Vec3();
			for (auto it = scene_->lights.begin(); it != scene_->lights.end(); it++) {
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
