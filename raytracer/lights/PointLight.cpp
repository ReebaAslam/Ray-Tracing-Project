#include "PointLight.hpp"
#include "./../utilities/RGBColor.hpp"
#include "./../utilities/Vector3D.hpp"
#include "./../utilities/ShadeInfo.hpp"
#include "./../utilities/Point3D.hpp"
#include "./../world/World.hpp"
#include "./../utilities/Ray.hpp"
#include "./../geometry/Geometry.hpp"
#include <cmath>


//citing -> chap 14 of Ray tracing from ground up
PointLight::PointLight() : 
	Light(), ls(1.0), color(1.0), location(0.0) {}

PointLight::PointLight(const PointLight &other) :
	Light(other), ls(other.ls), color(other.color), location(other.location) {}


Vector3D PointLight::getDirection(ShadeInfo & si) {
	Vector3D dir = location - si.hit_point;
	dir.normalize();
	return dir;
}
RGBColor PointLight::getL(ShadeInfo& si) {
	return color * ls;
}

RGBColor PointLight::getL(ShadeInfo& si, int attenuationPower=2) {
	auto r = (location - si.hit_point).length();
	return (color*ls) / std::pow(r, attenuationPower);
}

// citing -> chap 16 of raytracing from ground up
bool PointLight::in_shadow(const Ray& ray, const ShadeInfo& si) const {
	float t;
	float d = location.distance(ray.o);
	for (auto geom: si.w->geometry) {
		if (geom->shadow_hit(ray, t) && t < d) {
			return true;
		}
	}
	return false;
}

PointLight& PointLight::operator=(const PointLight &rhs) {
	if (this == &rhs) {
		return *this;
	}
	this->ls = rhs.ls;
	this->color = rhs.color;
	this->location = rhs.location;
	return *this;
}

void PointLight::scaleRadiance(const float ls) {
	this->ls = ls;
}
void PointLight::setColor(const RGBColor &col) {
	this->color = col;
}
void PointLight::setColor(const float c) {
	this->color = RGBColor(c);
}
void PointLight::setColor(const float r, const float g, const float b) {
	this->color = RGBColor(r, g, b);
}
void PointLight::setLocation(const Point3D &location) {
	this->location = location;
}

void PointLight::setLocation(const float x, const float y, const float z) {
	this->location = Point3D(x, y, z);
}

void PointLight::setLocation(const float p) {
	this->location = Point3D(p);
}

