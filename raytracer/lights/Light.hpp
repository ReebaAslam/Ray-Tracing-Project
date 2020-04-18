#pragma once
#include "./../utilities/ShadeInfo.hpp"
#include "./../world/World.hpp"
#include "./../utilities/Ray.hpp"
// class RGBColor;
// class Vector3D;
// class ShadeInfo;
// class Ray;

//citing -> https://github.com/busynight/First_Ray_Tracer/blob/master/wxraytracer/wxRaytracer/raytracer/Lights/Light.h

class Light {
protected:
	bool shadows;
public:
	Light();

	// Copy constuctor and assignment operator.
	Light(const Light &other);
	Light &operator=(const Light &other);

	virtual Vector3D getDirection(ShadeInfo & si) = 0;
	virtual RGBColor getL(ShadeInfo& si) = 0;

	void set_shadows(const bool s);

	bool casts_shadows() const;

	virtual bool in_shadow(const Ray& ray, const ShadeInfo& si) const;

	// Desctructor.
	virtual ~Light() = default;

};