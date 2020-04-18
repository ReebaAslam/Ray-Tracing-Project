#pragma once

#include <vector>

#include "Acceleration.hpp" 
#include "../geometry/Geometry.hpp" 
#include "../utilities/ShadeInfo.hpp" 
#include "../utilities/BBox.hpp" 
#include "../utilities/Ray.hpp"

//watched this before implementing, implemented myself https://www.youtube.com/watch?v=OJxEcs0w_kE
class Octree : public Acceleration {
protected:
	BBox box;
	int capacity; 
	bool divided; 
	std::vector<Geometry *> shapes;

	Octree* children[8]; 

public:
	Octree();
	Octree(BBox stuff, int num);
	~Octree();

	ShadeInfo hit_objects(const Ray &ray, ShadeInfo &shade) override;

	bool insert(Geometry* shape) override;

	void subdivide();
	void shapes_hit(Ray ray, ShadeInfo &shade, float& tmin);
};