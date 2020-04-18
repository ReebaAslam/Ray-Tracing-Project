#include <iostream>

#include "World.hpp"
#include "./../geometry/Geometry.hpp"
#include "./../cameras/Camera.hpp"
#include "./../utilities/ShadeInfo.hpp"
#include "./../utilities/Constants.hpp"
#include "./../materials/Material.hpp"
#include"./../utilities/RGBColor.hpp"
#include "../samplers/Sampler.hpp"
#include "../acceleration/Acceleration.hpp"
#include "../tracers/Tracer.hpp"
#include "../lights/Light.hpp"
#include "../lights/Ambient.hpp"

// Constructors.
World::World() {
	vplane = ViewPlane();
	bg_color = RGBColor();
	camera_ptr = NULL;
	sampler_ptr = NULL;
	tree = NULL;
	tracer = NULL;
	ambient_light = new Ambient();
}

// Destructor.
World::~World() {
	int num_geom = geometry.size();
	if (geometry.empty()) {
		for (int j = 0; j < num_geom; j++) {
			delete geometry[j];
			geometry[j] = NULL;
		}
		geometry.erase(geometry.begin(), geometry.end());
	}

	int num_lights = lights.size();
	if (lights.empty()) {
		for (int i = 0; i < num_lights; i++) {
			delete lights[i];
			lights[i] = NULL;
		}
		lights.erase(lights.begin(), lights.end());
	}

	delete sampler_ptr;
	delete camera_ptr;
	delete tracer;
	delete ambient_light;
} //citing: www.github.com/busynight/First_Ray_Tracer/blob/master/wxraytracer/wxRaytracer/raytracer/World/World.cpp

// Add to the scene.
void World::add_geometry(Geometry *geom_ptr) {
	geometry.push_back(geom_ptr);
}
void World::set_camera(Camera *c_ptr) {
	this->camera_ptr = c_ptr;
}

void World::add_light(Light *light_ptr){
	lights.push_back(light_ptr);
}

// Returns appropriate shading information corresponding to intersection of
// the ray with the scene geometry.
ShadeInfo World::hit_objects(const Ray &ray) {
	ShadeInfo shd(*this);
	float t;
	float tmin = kHugeValue;
	tree->hit_objects(ray, shd);
	return (shd);

	/*ShadeInfo shd(*this);
	float t;
	float tmin = kHugeValue;
	int num_geom = geometry.size();
	for (int i = 0; i < num_geom; i++) {
		// if (geometry[i]->hit(ray, t, shd) && t < tmin) {
		if (geometry[i]->hit(ray, tmin, shd)) {
			shd.hit = true;
			// tmin = t;
			shd.t = tmin;
			shd.material_ptr = geometry[i]->get_material();
		}
	}
	return (shd);*/
}

ShadeInfo World::hit_objects_raw(const Ray &ray) {
	// ShadeInfo shd(*this);
	// float t;
	// float tmin = kHugeValue;
	// tree->hit_objects(ray, shd);
	// return (shd);

	ShadeInfo shd(*this);
	float t;
	float tmin = kHugeValue;
	int num_geom = geometry.size();
	for (int i = 0; i < num_geom; i++) {
		// if (geometry[i]->hit(ray, t, shd) && t < tmin) {
		if (geometry[i]->hit(ray, tmin, shd)) {
			shd.hit = true;
			// tmin = t;
			shd.t = tmin;
			shd.material_ptr = geometry[i]->get_material();
		}
	}
	return (shd);
}