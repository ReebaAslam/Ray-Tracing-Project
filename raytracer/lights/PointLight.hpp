#pragma once

#include "Light.hpp"
#include "./../utilities/RGBColor.hpp"
#include "./../utilities/Vector3D.hpp"
#include "./../utilities/ShadeInfo.hpp"
#include "./../utilities/Point3D.hpp"
#include "./../world/World.hpp"
#include "./../utilities/Ray.hpp"
#include "./../geometry/Geometry.hpp"

//citing -> chap 14 of Ray tracing from ground up
class PointLight : public Light {
private:
	float ls;
	RGBColor color;
	Point3D location;
public:
	PointLight();
	PointLight(const PointLight &other);

	virtual Vector3D getDirection(ShadeInfo & si);
	virtual RGBColor getL(ShadeInfo& si);
	RGBColor getL(ShadeInfo& si, int attenuationPower);

	PointLight& operator=(const PointLight &rhs);

	virtual bool in_shadow(const Ray& ray, const ShadeInfo& si) const;

	void scaleRadiance(const float ls);
	void setColor(const RGBColor &col);
	void setColor(const float c);
	void setColor(const float r, const float g, const float b);
	void setLocation(const Point3D &location);
	void setLocation(const float x, const float y, const float z);
	void setLocation(const float p);


	virtual ~PointLight()=default;
};