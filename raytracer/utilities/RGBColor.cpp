//#include "stdafx.h"
#include "RGBColor.hpp"
#include <cmath>
#include <sstream>

float rangeValue(float val);

//constructor 
RGBColor::RGBColor(float _r, float _g, float _b) :
	r(rangeValue(_r)), g(rangeValue(_g)), b(rangeValue(_b)) {}

//parametrized constructors
RGBColor::RGBColor(float c) {
	c = rangeValue(c);
	r = c;
	g = c;
	b = c;
}

RGBColor::RGBColor() : r(0.0), g(0.0), b(0.0) {}

RGBColor RGBColor::operator+(const RGBColor &c) const {
	return RGBColor(rangeValue(r + c.r), rangeValue(g + c.g), rangeValue(b + c.b));
}

RGBColor& RGBColor:: operator+=(const RGBColor &c) {
	this->r = rangeValue(this->r + c.r);
	this->g = rangeValue(this->g + c.g);
	this->b = rangeValue(this->b + c.b);
	return *this;
}

RGBColor RGBColor::operator*(const float a) const {
	return RGBColor(rangeValue(r * a), rangeValue(g *a), rangeValue(b *a));
}

RGBColor& RGBColor::operator*=(const float a) {
	this->r = rangeValue(r * a);
	this->g = rangeValue(g * a);
	this->b = rangeValue(b * a);
	return *this;
}

RGBColor RGBColor:: operator/(const float a) const {
	return RGBColor(rangeValue(r / a), rangeValue(g / a), rangeValue(b / a));
}

RGBColor & RGBColor::operator/=(const float a) {
	this->r = rangeValue(r / a);
	this->g = rangeValue(g / a);
	this->b = rangeValue(b / a);
	return *this;
}

RGBColor RGBColor::operator*(const RGBColor &c) const {
	return RGBColor(rangeValue(r*c.r), rangeValue(g*c.g), rangeValue(b*c.b));
}

bool RGBColor::operator==(const RGBColor &c) const {
	return (r == c.r && g == c.g && b == c.b);
}

RGBColor RGBColor::powc(float p) const {
	return RGBColor(rangeValue(std::pow(r, p)), 
		rangeValue(std::pow(g, p)), 
		rangeValue(std::pow(b, p)));
}

float RGBColor::average() const {
	return (r + g + b) / 3;
}

RGBColor operator*(const float a, const RGBColor &c) {
	return RGBColor(rangeValue(a*c.r), rangeValue(a*c.g), rangeValue(a*c.b));
}

float rangeValue(float val) {
	return (val < 0.0) ? 0 : (val > 1.0) ? 1.0 : val;
}

std::string RGBColor::to_string() const {
	std::ostringstream ss;
	ss << "Color(" << r << ", " << g << ", " << b << ")";
	return ss.str();
}
