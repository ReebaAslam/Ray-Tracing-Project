#pragma once
#pragma once

#include "Light.hpp"
#include "./../utilities/RGBColor.hpp"
#include "./../utilities/Vector3D.hpp"
#include "./../utilities/ShadeInfo.hpp"
#include "./../utilities/Ray.hpp"

//citing -> chap 14 of Ray tracing from ground up
class Directional : public Light {
private:
	float ls;
	RGBColor color;
	Vector3D direction;	//default direction is set to be downwards in the constructor
public:
	Directional();	
	Directional(const Directional &other);

	virtual Vector3D getDirection(ShadeInfo & si);
	virtual RGBColor getL(ShadeInfo& si);
	Directional& operator=(const Directional &rhs);

	virtual bool in_shadow(const Ray& ray, const ShadeInfo& si) const;

	void scaleRadiance(const float ls);
	void setColor(const RGBColor &col);
	void setColor(const float c);
	void setColor(const float r, const float g, const float b);
	void setDirection(const Vector3D &location);
	void setDirection(const float x, const float y, const float z);
	void setDirection(const float p);


	virtual ~Directional() = default;
};