#include "Directional.hpp"
#include "./../utilities/RGBColor.hpp"
#include "./../utilities/Vector3D.hpp"
#include "./../utilities/ShadeInfo.hpp"
#include "./../utilities/Ray.hpp"
#include "./../geometry/Geometry.hpp"
#include <cmath>

//citing -> chap 14 of Ray tracing from ground up
Directional::Directional() :
	Light(), ls(1.0), color(1.0), direction(0.0, 1.0, 0.0) {}	

Directional::Directional(const Directional &other) :
	Light(other), ls(other.ls), color(other.color), direction(other.direction) {}


Vector3D Directional::getDirection(ShadeInfo & si) {
	direction.normalize();
	return direction;
}
RGBColor Directional::getL(ShadeInfo& si) {
	return color * ls;
}

bool Directional::in_shadow(const Ray& ray, const ShadeInfo& si) const {
	float t;
	for (auto geom: si.w->geometry) {
		if (geom->shadow_hit(ray, t)) {
			return true;
		}
	}
	return false;
}
Directional& Directional::operator=(const Directional &rhs) {
	if (this == &rhs) {
		return *this;
	}
	this->ls = rhs.ls;
	this->color = rhs.color;
	this->direction = rhs.direction;
	return *this;
}

void Directional::scaleRadiance(const float ls) {
	this->ls = ls;
}
void Directional::setColor(const RGBColor &col) {
	this->color = col;
}
void Directional::setColor(const float c) {
	this->color = RGBColor(c);
}
void Directional::setColor(const float r, const float g, const float b) {
	this->color = RGBColor(r, g, b);
}
void Directional::setDirection(const Vector3D &direction) {
	this->direction = direction;
}

void Directional::setDirection(const float x, const float y, const float z) {
	this->direction = Vector3D(x, y, z);
}

void Directional::setDirection(const float p) {
	this->direction = Vector3D(p);
}

