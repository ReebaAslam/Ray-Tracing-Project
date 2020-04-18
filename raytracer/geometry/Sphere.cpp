#include "Sphere.hpp"
#include <cmath>
#include <sstream>
#include "../utilities/BBox.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"

Sphere::Sphere() : c(0.0), r(0.0) {}

Sphere::Sphere(const Point3D &center, float radius) : c(center), r(radius) {}

Sphere::Sphere(const Sphere &object)
    : c(object.c), r(object.r), Geometry(object) {}

Sphere &Sphere::operator=(const Sphere &rhs) {
    if (this == &rhs) {
        return (*this);
    }

    Geometry::operator=(rhs);
    c = rhs.c;
    r = rhs.r;
    return (*this);
}

std::string Sphere::to_string() const {
    std::ostringstream ss;
    ss << "Center: " << c.to_string() << "/n Radius: " << r;
    return ss.str();
}

bool Sphere::hit(const Ray &ray, float &t, ShadeInfo &s) const {
    float t_temp;
    Vector3D temp = ray.o - c;
    double a = ray.d * ray.d;
    double b = (2.0 * temp) * ray.d;
    double c = (temp * temp) - (r * r);
    double disc = (b * b) - (4.0 * a * c);

    if (disc < 0.0) {
        return false;
    } else {
        double e = std::sqrt(disc);
        double denom = 2.0 * a;
        t_temp = (-b - e) / denom;  // smaller root

        if (t_temp > kEpsilon && t_temp < t) {
            t = t_temp;
            s.normal = (temp + t * ray.d) / r;
            s.normal.normalize();
            s.hit_point = ray.o + t * ray.d;
            s.ray = ray;

            return (true);
        }

        t_temp = (-b + e) / denom;  // bigger root

        if (t_temp > kEpsilon && t_temp < t) {
            t = t_temp;
            s.normal = (temp + t * ray.d) / r;
            s.normal.normalize();
            s.hit_point = ray.o + t * ray.d;
            s.ray = ray;

            return (true);
        }
    }

    return (false);
}  // citing chapter 3 of book

bool Sphere::shadow_hit(const Ray &ray, float &tmin) const {
	float t_temp;
    Vector3D temp = ray.o - c;
    double a = ray.d * ray.d;
    double b = (2.0 * temp) * ray.d;
    double c = (temp * temp) - (r * r);
    double disc = (b * b) - (4.0 * a * c);
	if (disc < 0.0) {
		return false;
	}
	else {
		double e = std::sqrt(disc);
		double denom = 2.0 * a;
		t_temp = (-b - e) / denom;  // smaller root

		if (t_temp > kEpsilon && t_temp < tmin) {
			tmin = t_temp;
			return (true);
		}

		t_temp = (-b + e) / denom;  // bigger root

		if (t_temp > kEpsilon && t_temp < tmin) {
			tmin = t_temp;
			return (true);
		}
	}
	return (false);
}

BBox Sphere::getBBox() const {
    Vector3D vec_r = Vector3D(r);
    Point3D pmin = c - vec_r;
    Point3D pmax = c + vec_r;
    return BBox(pmin, pmax);
}

Point3D Sphere::mid_point(){
    return c; 
}