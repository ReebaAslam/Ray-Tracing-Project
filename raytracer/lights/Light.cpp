#include "Light.hpp"
#include "./../utilities/ShadeInfo.hpp"
#include "./../world/World.hpp"
#include "./../utilities/Ray.hpp"

Light::Light() : shadows(false) {}

Light::Light(const Light& l) : shadows(l.shadows) {}

Light& Light::operator=(const Light& rhs) {

	if (this == &rhs)
		return *this;

	shadows = rhs.shadows;
	return *this;
}
bool Light::in_shadow(const Ray& ray, const ShadeInfo& si) const {
	return false;
}

void Light::set_shadows(const bool s) {
	this->shadows = s;
}

bool Light::casts_shadows() const{
	return shadows;
}