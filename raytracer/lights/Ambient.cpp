
#include "Ambient.hpp"
#include "./../utilities/RGBColor.hpp"
#include "./../utilities/Vector3D.hpp"
#include "./../utilities/ShadeInfo.hpp"
#include "./../utilities/Ray.hpp"

//citing -> chap 14 of Ray tracing from ground up
Ambient::Ambient() : Light(), ls(1.0), color(1.0){}

Ambient::Ambient(const Ambient &other) : Light(other), ls(other.ls), color(other.color) {}

Ambient& Ambient::operator=(const Ambient &rhs) {
	if (this == &rhs) {
		return *this;
	}
	this->ls = rhs.ls;
	this->color = rhs.color;
	return *this;
}

Vector3D Ambient::getDirection(ShadeInfo & si) {
	return Vector3D(0.0);
}

RGBColor Ambient::getL(ShadeInfo& si) {
	return color * ls;
}

void Ambient::setColor(const RGBColor &col) {
	this->color = col;
}

void Ambient::setColor(const float c) {
	this->color = RGBColor(c);
}

void Ambient::setColor(const float r, const float g, const float b ) {
	this->color = RGBColor(r,g,b);
}

void Ambient::scaleRadiance(const float ls) {
	this->ls = ls;
}