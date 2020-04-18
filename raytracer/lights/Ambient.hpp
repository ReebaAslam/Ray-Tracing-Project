#pragma once

#include "Light.hpp"
#include "./../utilities/RGBColor.hpp"
#include "./../utilities/Vector3D.hpp"
#include "./../utilities/ShadeInfo.hpp"
#include "./../utilities/Ray.hpp"

// class RGBColor;
// class ShadeInfo;
// class Vector3D;
// class Ray;

//citing -> chap 14 of Ray tracing from ground up
class Ambient : public Light {
private:
	float ls;
	RGBColor color; 
public:
	Ambient();
	Ambient(const Ambient &other);

	virtual Vector3D getDirection(ShadeInfo & si);
	virtual RGBColor getL(ShadeInfo& si);

	Ambient& operator=(const Ambient &rhs);

	void scaleRadiance(const float ls);
	void setColor(const RGBColor &col);
	void setColor(const float c);
	void setColor(const float r, const float g, const float b);

	virtual ~Ambient()=default;

};