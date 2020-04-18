//#include "stdafx.h"
#include "Ray.hpp"
#include <sstream>

// constructor with parameters
Ray::Ray(const Point3D &origin, const Vector3D &dir) {
	o = origin;
	d = dir;
	d.normalize();
	w = 1.0;
}

// constructor
Ray::Ray() {
	o = Point3D(0.0, 0.0, 0.0);
	d = Vector3D(0.0, 0.0, 0.0);
	w = 1.0;
}

std::string Ray::to_string() const {
	std::ostringstream ss;
	ss << "Ray(" << o.to_string() << ", " << d.to_string() << ", " << w << ")";
	return ss.str();
}