#include "ViewPlane.hpp"
#include "./../utilities/Point3D.hpp"
#include "./../utilities/Vector3D.hpp"

ViewPlane::ViewPlane() {
	hres = 640;
	vres = 480;
	top_left = Point3D(-320, 240, 0);
	bottom_right = Point3D(320, -240, 0);
	normal = Vector3D(top_left) ^ Vector3D(bottom_right);
	max_depth = 0;
}


// Get/set resolution.
int ViewPlane::get_hres() const {
	return hres;
}
void ViewPlane::set_hres(int val) {
	this->hres = val;
}
int ViewPlane::get_vres() const {
	return vres;
}
void ViewPlane::set_vres(int val) {
	this->vres = val;
}
