#include "Triangle.hpp"
#include <sstream>
#include "../utilities/BBox.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Point3D.hpp"

float getMin(float a, float b, float c);
float getMax(float a, float b, float c);

Triangle::Triangle() : v0(0.0), v1(0.0), v2(0.0) {}

Triangle::Triangle(const Point3D &v0, const Point3D &v1, const Point3D &v2)
    : v0(v0), v1(v1), v2(v2) {}

Triangle::Triangle(const Triangle &object)
    : v0(object.v0), v1(object.v1), v2(object.v2), Geometry(object) {}

Triangle &Triangle::operator=(const Triangle &rhs) {
    if (this == &rhs) {
        return (*this);
    }

    Geometry::operator=(rhs);
    v0 = rhs.v0;
    v1 = rhs.v1;
    v2 = rhs.v2;
    return (*this);
}

std::string Triangle::to_string() const {
    std::ostringstream ss;
    ss << "Triangle(" << v0.to_string() << ", " << v1.to_string() << ", "
       << v2.to_string() << ")";
    return ss.str();
}

bool Triangle::hit(const Ray &ray, float &t, ShadeInfo &s) const {
    Vector3D edge1 = v1 - v0;
    Vector3D edge2 = v2 - v0;
    Vector3D e2_cross_d = ray.d ^ edge2;

    float det = edge1 * e2_cross_d;
    if (det > -kEpsilon && det < kEpsilon) {  // checking absolute value of det
                                              // to see if it's closer to zero
        return (false);                       // ray is parallel to triangle
    }

    float invDet = 1.0 / det;
    Vector3D tvec = ray.o - v0;

    // calculating beta
    float beta = (tvec * e2_cross_d) * invDet;
    if (beta < 0 || beta > 1) {
        return (false);
    }

    // calculating gamma
    Vector3D qvec = tvec ^ edge1;
    float gamma = (qvec * ray.d) * invDet;
    if (gamma < 0 || beta + gamma > 1) {
        return (false);
    }

    // calculating t
    float t_temp = (qvec * edge2) * invDet;
    if (t_temp < kEpsilon) {
        return (false);  // no ray intersection but there is line intersection
    }

    if (t_temp < t) {
        t = t_temp;
        s.normal = edge1 ^ edge2;
        s.normal.normalize();
        s.hit_point = ray.o + t * ray.d;
        s.ray = ray;
        return (true);
    }

    return (false);

}  // using Möller–Trumbore intersection algorithm
   // (https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection)

BBox Triangle::getBBox() const {

    /*Point3D pmin = min(v2, min(v0, v1));
    Point3D pmax = max(v0, max(v0, v1));*/ 
    Point3D p0;
    Point3D p1;

    p0.x = getMin(v0.x, v1.x, v2.x);
    p0.y = getMin(v0.y, v1.y, v2.y);
    p0.z = getMin(v0.z, v1.z, v2.z);

    p1.x = getMax(v0.x, v1.x, v2.x);
    p1.y = getMax(v0.y, v1.y, v2.y);
    p1.z = getMax(v0.z, v1.z, v2.z);

    return BBox(p0,p1);
    
}

Point3D Triangle::mid_point(){
    return Point3D( (v0.x + v1.x + v2.x)/3,
                    (v0.y + v1.y + v2.y)/3,
                    (v0.z + v1.z + v2.z)/3);
}

bool Triangle::shadow_hit(const Ray &ray, float &tmin) const{
	Vector3D edge1 = v1 - v0;
	Vector3D edge2 = v2 - v0;
	Vector3D e2_cross_d = ray.d ^ edge2;

	float det = edge1 * e2_cross_d;
	if (det > -kEpsilon && det < kEpsilon) {  // checking absolute value of det
											  // to see if it's closer to zero
		return (false);                       // ray is parallel to triangle
	}

	float invDet = 1.0 / det;
	Vector3D tvec = ray.o - v0;

	// calculating beta
	float beta = (tvec * e2_cross_d) * invDet;
	if (beta < 0 || beta > 1) {
		return (false);
	}

	// calculating gamma
	Vector3D qvec = tvec ^ edge1;
	float gamma = (qvec * ray.d) * invDet;
	if (gamma < 0 || beta + gamma > 1) {
		return (false);
	}

	// calculating t
	float t_temp = (qvec * edge2) * invDet;
	if (t_temp < kEpsilon) {
		return (false);  // no ray intersection but there is line intersection
	}

	if (t_temp < tmin) {
		tmin = t_temp;
		return (true);
	}

	return (false);
}

float getMin(float a, float b, float c){

    if (a <= b && a <= c){
        return a - kEpsilon;
    }else if (b <= a && b <= c){
        return b - kEpsilon;
    }else{
        return c - kEpsilon;
    }

}

float getMax(float a, float b, float c){
    if (a >= b && a >= c){
        return a + kEpsilon;
    }else if (b >= a && b >= c){
        return b + kEpsilon;
    }else{
        return c + kEpsilon;
    }
}