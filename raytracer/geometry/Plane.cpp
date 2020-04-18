#include "Plane.hpp"
#include <sstream>
#include "../utilities/BBox.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"

// set plane to xz-plane
Plane::Plane() : a(0.0), n(0.0, 1.0, 0.0) {}

Plane::Plane(const Point3D &pt, const Vector3D &n) : a(pt), n(n) {
    this->n.normalize();
}

Plane::Plane(const Plane &object)
    : a(object.a), n(object.n), Geometry(object) {}

Plane &Plane::operator=(const Plane &rhs) {
    if (this == &rhs) {
        return (*this);
    }

    Geometry::operator=(rhs);
    a = rhs.a;
    n = rhs.n;
    return (*this);
}

std::string Plane::to_string() const {
    std::ostringstream ss;
    ss << "Point on the plane: " << a.to_string()
       << "/n Normal to the plane: " << n.to_string();
    return ss.str();
}

// Ray intersection. Set t and sinfo as per intersection with this object.
bool Plane::hit(const Ray &ray, float &t, ShadeInfo &s) const {
    float t_temp = ((a - ray.o) * n) / (ray.d * n);
    if (t_temp > kEpsilon && t_temp < t) {
        t = t_temp;
        s.normal = n;
        s.normal.normalize();
        s.hit_point = ray.o + (t * ray.d);
        s.ray = ray;
        
        return (true);
    }
    return (false);
}  // citing chapter 3 of book

bool Plane::shadow_hit(const Ray &ray, float &tmin) const {
	float t = ((a - ray.o)*n) / (ray.d *n);
	if (t > kEpsilon && t < tmin) {
		tmin = t;
		return true;
	}
	else {
		return false;
	}
}

// Get bounding box.
BBox Plane::getBBox() const {
    // stub function
    return BBox();
}

Point3D Plane::mid_point(){
    return this->a; 
}