
#include <cmath>
#include <iostream>

#include "Grid.hpp"

#include "../utilities/BBox.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Ray.hpp"



Grid::Grid(){}
Grid::~Grid(){}
BBox Grid::get_bounding_box(){}
bool Grid::hit(Ray& ray, float& tmin, ShadeInfo& s){}
bool Grid::insert(Geometry* shape){
	shapes.push_back(shape);
}
ShadeInfo Grid::hit_objects(const Ray &ray, ShadeInfo &shade){}

Point3D Grid::min_coordinates(){
	BBox bbox; 
	Point3D p0(kHugeValue);

	for(auto shape: shapes){
		bbox  = shape->getBBox();
		if (bbox.pmin.x < p0.x){
			p0.x = bbox.pmin.x;
		}
		if (bbox.pmin.y < p0.y){
			p0.y = bbox.pmin.y;
		}
		if (bbox.pmin.z < p0.z){
			p0.z = bbox.pmin.z;
		}
	}
	p0.x -= kEpsilon;
	p0.y -= kEpsilon;
	p0.z -= kEpsilon;

	return p0;
}
Point3D Grid::max_coordinates(){
	BBox bbox; 
	Point3D p0(kHugeValue);

	for(auto shape: shapes){
		bbox  = shape->getBBox();
		if (bbox.pmax.x > p0.x){
			p0.x = bbox.pmax.x;
		}
		if (bbox.pmax.y > p0.y){
			p0.y = bbox.pmax.y;
		}
		if (bbox.pmax.z > p0.z){
			p0.z = bbox.pmax.z;
		}
	}
	p0.x += kEpsilon;
	p0.y += kEpsilon;
	p0.z += kEpsilon;

	return p0;
}

void Grid::setup_cells(){
	/*std::cout<<"AAAA\n";
	box.pmin = min_coordinates();
	box.pmax = max_coordinates();

	int num_objects = shapes.size();
	float wx = box.pmax.x = box.pmin.x;
	float wy = box.pmax.y = box.pmin.y;
	float wz = box.pmax.z = box.pmin.z;

	float multiplier = 2.0;

	float s = pow(wx*wy*wz/ num_objects, 1/3);
	this -> nx = (multiplier*wx/s) + 1;
	this -> ny = (multiplier*wy/s) + 1;
	this -> nz = (multiplier*wz/s) + 1;

	int num_cells = nx * ny * nz;

	std::vector<int> counts;
	counts.reserve(num_cells);

	for (int i=0; i<num_cells; i++){
		cells.push_back(NULL);
		counts.push_back(0);
	}

	BBox obj_box; 
	int index; 
	std::cout<<"BBBB\n";
	for (auto obj: shapes){
		obj_box = obj->getBBox();

		int ixmin = clamp((obj_box.pmin.x - box.pmin.x)*nx/(box.pmax.x - box.pmin.x), 0, nx-1);
		int iymin = clamp((obj_box.pmin.y - box.pmin.y)*ny/(box.pmax.y - box.pmin.y), 0, ny-1);
		int izmin = clamp((obj_box.pmin.z - box.pmin.z)*nz/(box.pmax.z - box.pmin.z), 0, nz-1);
		int ixmax = clamp((obj_box.pmax.x - box.pmin.x)*nx/(box.pmax.x - box.pmin.x), 0, nx-1);
		int iymax = clamp((obj_box.pmax.y - box.pmin.y)*ny/(box.pmax.y - box.pmin.y), 0, ny-1);
		int izmax = clamp((obj_box.pmax.z - box.pmin.z)*nz/(box.pmax.z - box.pmin.z), 0, nz-1);
	
		std::cout<<"CCCC\n";
		for (int iz = izmin; iz <= izmax; iz++){
			for (int iy = iymin; iy <= iymax; iy++){
				for (int ix = ixmin; ix <= ixmax; ix++){
					index = ix + nx & iy + nx * ny * iz;

					cells[index].push_back(obj);
					counts[index] += 1;
					std::cout<<"DDDD\n";	
					
				}		
			}
		}
	}
	shapes.erase(shapes.begin(), shapes.end());
	counts.erase(counts.begin(), counts.end());
*/
}