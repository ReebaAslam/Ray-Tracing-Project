#pragma once

#include <vector>
#include "../geometry/Geometry.hpp" 
#include "../utilities/ShadeInfo.hpp" 
#include "../utilities/BBox.hpp" 

class Acceleration{
	
public:
	Acceleration() = default;
  	
  	virtual ~Acceleration() = default;

  	virtual ShadeInfo hit_objects(const Ray &ray, ShadeInfo &shade) = 0;
  	//virtual bool hit_objects(Acceleration* node, const Ray &ray, float& t, float&tmin, ShadeInfo &shade) = 0;

  	virtual bool insert(Geometry* shape) = 0;

  	virtual Acceleration* build(std::vector<Geometry*>& shapes, int depth){}

  	virtual void setup_cells(){}

};