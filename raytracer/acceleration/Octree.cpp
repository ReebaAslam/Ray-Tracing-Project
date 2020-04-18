#include <vector>
#include <iostream>

#include "Octree.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Ray.hpp"

Octree::Octree(){

}

Octree::~Octree(){
	if (this->divided){
		for (auto child: children){
			child->~Octree();
			delete child;
			child = NULL;
		}
	}
}

Octree::Octree(BBox stuff, int num){

	this->capacity = num;
	this->divided = false; 
	this->box = stuff;
	
}

void Octree::shapes_hit(Ray ray, ShadeInfo &shade, float& tmin){
	float t1;
	float t2;
	
	if (!this->box.hit(ray, t1, t2)){
		return;
	}
	for (auto shape: shapes){

		if (shape->hit(ray, tmin, shade)) {

			shade.hit = true;
			shade.t = tmin;
			shade.material_ptr = shape->get_material();
		}
	}
	
	if (this->divided){
		for(auto child: children){
			
			child->shapes_hit(ray, shade, tmin);
		}
	}
}

ShadeInfo Octree::hit_objects(const Ray &ray, ShadeInfo &shade){
	
	float t;
	float tmin = kHugeValue;

	shapes_hit(ray, shade, tmin);

	return shade;

}

bool Octree::insert(Geometry* shape){

	if (!this->box.overlaps(shape)){
		return false; 
	}

	if (this->shapes.size() <= this->capacity){
		this->shapes.push_back(shape);
		return true;
	}
	else{
		if (!this->divided){
			this->subdivide();	
			
		}	
		bool inserted = false;
		for(auto child: this->children){
			if (child -> insert(shape)){
				inserted = true;
			}
		}
		return inserted; 
	}
}

void Octree::subdivide(){

	Point3D center( (box.pmin.x + box.pmax.x)/2,
					(box.pmin.y + box.pmax.y)/2,
					(box.pmin.z + box.pmax.z)/2); 

	children[0] = new Octree(BBox(box.pmin, center), this->capacity);
	children[1] = new Octree(BBox(center, box.pmax), this->capacity);

	children[2] = new Octree(BBox(Point3D(box.pmin.x, (box.pmin.y + box.pmax.y)/2, box.pmin.z),
								  Point3D((box.pmin.x + box.pmax.x)/2, box.pmax.y, (box.pmin.z + box.pmax.z)/2)), this->capacity);

	children[3] = new Octree(BBox(Point3D(box.pmin.x, (box.pmin.y + box.pmax.y)/2, (box.pmin.z + box.pmax.z)/2),
								  Point3D((box.pmin.x + box.pmax.x)/2, box.pmax.y, box.pmax.z)), this->capacity);

	children[4] = new Octree(BBox(Point3D(box.pmin.x, box.pmin.y, (box.pmin.z + box.pmax.z)/2),
	 							  Point3D((box.pmin.x + box.pmax.x)/2,(box.pmin.y + box.pmax.y)/2,box.pmax.z)), this->capacity);

	children[5] = new Octree(BBox(Point3D((box.pmin.x + box.pmax.x)/2,box.pmin.y,(box.pmin.z + box.pmax.z)/2),
	 							  Point3D(box.pmax.x, (box.pmin.y + box.pmax.y)/2 ,box.pmax.z)), this->capacity);

	children[6] = new Octree(BBox(Point3D((box.pmin.x + box.pmax.x)/2,box.pmin.y, box.pmin.z),
	 							  Point3D(box.pmax.x, (box.pmin.y + box.pmax.y)/2, (box.pmin.z + box.pmax.z)/2)), this->capacity);

	children[7] = new Octree(BBox(Point3D((box.pmin.x + box.pmax.x)/2, (box.pmin.y + box.pmax.y)/2, box.pmin.z),
								  Point3D(box.pmax.x, box.pmax.y, (box.pmin.z + box.pmax.z)/2)), this->capacity);

	this->divided = true;
}
