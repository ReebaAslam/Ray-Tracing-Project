//#include "stdafx.h"
#include "ShadeInfo.hpp"
#include "./../world/World.hpp"

ShadeInfo::ShadeInfo(const World &wr): 
	hit(false), 
	material_ptr(NULL), 
	hit_point(Point3D()), 
	normal(Vector3D()),
	ray(Ray()),
	depth(0),
	t(0),
	w(&wr){}