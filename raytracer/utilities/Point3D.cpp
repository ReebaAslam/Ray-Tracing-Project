//#include "stdafx.h"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <sstream>
#include <cmath>


Point3D::Point3D(float x, float y, float z) : x(x), y(y), z(z) {}

Point3D::Point3D(float c) : x(c), y(c), z(c){}

Point3D::Point3D(): x(0), y(0), z(0) {}

std::string Point3D::to_string() const {
	std::ostringstream ss;
	ss << "Point(" << x << ", " << y << ", " << z << ")";
	return ss.str();
}

Point3D Point3D::operator-() const {
    return Point3D(-x, -y, -z);
}

Vector3D Point3D::operator-(const Point3D &p) const {
	return Vector3D(x - p.x, y - p.y, z - p.z);
}

Point3D Point3D::operator+(const Vector3D &v) const {
	return Point3D(x + v.x, y + v.y, z + v.z);
}

Point3D Point3D::operator-(const Vector3D &v) const {
	return Point3D(x - v.x, y - v.y, z - v.y);
}

Point3D Point3D::operator*(const float s) const {
	return Point3D(x*s, y*s, z*s);
}
											
float Point3D::d_squared(const Point3D &p) const {
	return std::pow(this->distance(p), 2);
}

float Point3D::distance(const Point3D &p) const {
	auto dist = *this - p;
	auto sum = std::pow(dist.x, 2) + std::pow(dist.y, 2) + std::pow(dist.z, 2);
	return std::sqrt(sum);
}

// Scale pt by a factor, s.
Point3D operator*(const float a, const Point3D &pt) {
	return Point3D(a*pt.x, a*pt.y, a*pt.z);
}

// Compare points.
Point3D min(const Point3D& a, const Point3D& b) {
	return Point3D(std::fmin(a.x, b.x), std::fmin(a.y, b.y), std::fmin(a.z, b.z));
}

Point3D max(const Point3D& a, const Point3D& b) {
	return Point3D(std::fmax(a.x, b.x), std::fmax(a.y, b.y), std::fmax(a.z, b.z));
}

