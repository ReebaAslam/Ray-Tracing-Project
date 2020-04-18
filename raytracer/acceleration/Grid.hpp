#pragma once

#include <vector>

#include "Acceleration.hpp" 

#include "../geometry/Geometry.hpp" 
#include "../utilities/ShadeInfo.hpp" 
#include "../utilities/BBox.hpp" 
#include "../utilities/Ray.hpp"


//From the book, ray tracing from the ground-up
class Grid : public Acceleration{

protected:
	std::vector<std::vector<Geometry*> > cells;
	std::vector<Geometry*> shapes;
	BBox box;
	int nx, ny, nz;

	Point3D min_coordinates();
	Point3D max_coordinates();

public:

	Grid();
	~Grid();
	BBox get_bounding_box();
	bool hit(Ray& ray, float& tmin, ShadeInfo& s);
	void setup_cells();
	bool insert(Geometry* shape) override; 
	ShadeInfo hit_objects(const Ray &ray, ShadeInfo &shade) override;
};

inline float clamp(float x, float min, float max){
	return (x < min ? min : (x > max? max : x));
}