#include "Cosine.hpp"
#include "../utilities/ShadeInfo.hpp"
#include <iostream>

Cosine::Cosine() : color(0.0) {}

Cosine::Cosine(float c) : color(c) {}

Cosine::Cosine(float r, float g, float b) : color(r, g, b) {}

Cosine::Cosine(const RGBColor &c) : color(c) {}

Cosine::Cosine(const Cosine &other) : Material(other), color(other.color) {}

Cosine &Cosine::operator=(const Cosine &other) {
    if (this == &other) {
        return (*this);
    }

    Material::operator=(other);  // only required if default assignment operator
                                 // is changed to do something
    color = other.color;
    return (*this);
}

RGBColor Cosine::shade(const ShadeInfo &sinfo) const {
    /* Returned shade is: color * cos \theta.
     \theta is the angle between the normal at the hit pont and the ray.
     Assuming unit vectors, cos \theta = dot product of normal and -ray.dir.
    */
   float cos = sinfo.normal * -sinfo.ray.d;
   return color * cos;
}