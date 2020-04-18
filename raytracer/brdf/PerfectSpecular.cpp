#include "PerfectSpecular.hpp"
#include <cmath>
#include "../utilities/Constants.hpp"
#include "../utilities/ShadeInfo.hpp"

// from chapter 24 of Ray Tracing from the Ground Up
PerfectSpecular::PerfectSpecular() : kr(0.0), cr(0.0) {}

PerfectSpecular::PerfectSpecular(float kr, RGBColor cr) : kr(kr), cr(cr) {}

PerfectSpecular::PerfectSpecular(const PerfectSpecular &brdf)
    : kr(brdf.kr), cr(brdf.cr), BRDF(brdf) {}

PerfectSpecular &PerfectSpecular::operator=(const PerfectSpecular &other) {
    if (this == &other) {
        return (*this);
    }

    BRDF::operator=(other);
    kr = other.kr;
    cr = other.cr;
    return (*this);
}

void PerfectSpecular::set_cr(RGBColor cs) { this->cr = cr; }

void PerfectSpecular::set_kr(float kr) { this->kr = kr; }

// from chapter 24 of Ray Tracing from the Ground Up
RGBColor PerfectSpecular::rho(const ShadeInfo &sr, const Vector3D &wo) const {
    return (black);
}

// from chapter 24 of Ray Tracing from the Ground Up
RGBColor PerfectSpecular::f(const ShadeInfo &sr, const Vector3D &wi,
                            const Vector3D &wo) const {
    return (black);
}

// from chapter 24 of Ray Tracing from the Ground Up
RGBColor PerfectSpecular::sample_f(const ShadeInfo &sr, Vector3D &wi,
                                   const Vector3D &wo) const {
    float ndotwo = sr.normal * wo;
    wi = -wo + 2.0 * sr.normal * ndotwo;        // reflected direction

    return (kr * cr / (sr.normal * wi));
}