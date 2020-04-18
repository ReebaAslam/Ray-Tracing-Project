//#include "stdafx.h"
#include "BBox.hpp"
#include "Point3D.hpp"
#include "Ray.hpp"
#include "Constants.hpp"
#include "./../geometry/Geometry.hpp"
#include <sstream>
#include <cmath>

BBox::BBox(const Point3D& min, const Point3D& max) : pmin(min), pmax(max) {}

std::string BBox::to_string() const {
	std::ostringstream ss;
	ss << "BBox(" << pmin.to_string() << ", " << pmax.to_string() << ")";
	return ss.str();
}

// Does ray hit bbox? If so, set entering and leaving t values for ray.
bool BBox::hit(const Ray &ray, float &t_enter, float &t_exit) const {
	double invX = 1 / ray.d.x, invY = 1 / ray.d.y, invZ = 1 / ray.d.z;
	int sign[3];
	sign[0] = invX < 0;
	sign[1] = invY < 0;
	sign[2] = invZ < 0;
	Point3D bounds[2] = { pmin, pmax };
	double tMinX, tMinY, tMinZ;
	double tMaxX, tMaxY, tMaxZ;

	tMinX = (bounds[sign[0]].x - ray.o.x) * invX;
	tMaxX = (bounds[1 - sign[0]].x - ray.o.x) * invX;
	tMinY = (bounds[sign[1]].y - ray.o.y) * invY;
	tMaxY = (bounds[1 - sign[1]].y - ray.o.y) * invY;
	tMinZ = (bounds[sign[2]].z - ray.o.z) * invZ;
	tMaxZ = (bounds[1 - sign[2]].z - ray.o.z) * invZ;

	t_enter = std::fmax(tMinX, tMinY);
	t_enter = std::fmax(t_enter, tMinZ);

	t_exit = std::fmin(tMaxX, tMaxY);
	t_exit = std::fmin(t_exit, tMaxZ);

	return (t_enter<t_exit && t_exit>kEpsilon);
	

}//citing: Book Chap 19 and www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection

// Extend this bbox, if necessary, to include g or b.
void BBox::extend(Geometry* g) {
	this->extend(g->getBBox());

}
void BBox::extend(const BBox& b) {
	this->pmin = min(b.pmin, this->pmin);
	this->pmax = max(b.pmax, this->pmax);
}
// Does this BBox contain p? True even when p lies on a boundary.
bool BBox::contains(const Point3D& p) {
	bool lessX = p.x >= pmin.x && p.x <= pmax.x;	//x inside min and max x range
	bool lessY = p.y >= pmin.y && p.y <= pmax.y;	//y inside min and max y range
	bool lessZ = p.z >= pmin.z && p.z <= pmax.z;	//z inside min and max z range
	return lessX && lessY && lessZ;
}

// Does this BBox overlap with g or b?
bool BBox::overlaps(Geometry* g) {
	return this->overlaps(g->getBBox());
}
bool BBox::overlaps(const BBox& b) {
	//non overlapping conditions
	//one box at left
	if (b.pmax.x < pmin.x || b.pmin.x > pmax.x) {
		return false;
	}
	//one box below
	if (b.pmax.y < pmin.y || b.pmin.y > pmax.y) {
		return false;
	}
	//one box in front
	if (b.pmax.z < pmin.z || b.pmin.z > pmax.z) {
		return false;
	}
	return true;
}

int BBox::longest_axis(){
	float xdif = pmax.x - pmin.x;
	float ydif = pmax.y - pmin.y;
	float zdif = pmax.z - pmin.z;

	if (xdif >= ydif && xdif >= zdif) {
		return 0;
	}
	if (ydif >= xdif && ydif >= zdif) {
		return 1;
	}
	return 2;
}