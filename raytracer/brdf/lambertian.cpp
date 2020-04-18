#include "Lambertian.hpp"
#include "../utilities/Constants.hpp"

float clamp_kd(float kd);

// from chapter 13 of Ray Tracing from the Ground Up
Lambertian::Lambertian() : kd(0.0), cd(0.0) {}

Lambertian::Lambertian(float kd, RGBColor cd) : kd(clamp_kd(kd)), cd(cd) {}

Lambertian::Lambertian(const Lambertian &brdf)
    : kd(brdf.kd), cd(brdf.cd), BRDF(brdf) {}

Lambertian &Lambertian::operator=(const Lambertian &other) {
    if (this == &other) {
        return (*this);
    }

    BRDF::operator=(other);
    kd = other.kd;
    cd = other.cd;
    return (*this);
}

// from chapter 13 of Ray Tracing from the Ground Up
void Lambertian::set_cd(RGBColor cd) { this->cd = cd; }

// from chapter 13 of Ray Tracing from the Ground Up
void Lambertian::set_kd(float kd) { this->kd = clamp_kd(kd); }

// from chapter 13 of Ray Tracing from the Ground Up
RGBColor Lambertian::rho(const ShadeInfo &sr, const Vector3D &wo) const {
    return (kd * cd);
}

// from chapter 13 of Ray Tracing from the Ground Up
RGBColor Lambertian::f(const ShadeInfo &sr, const Vector3D &wi,
                       const Vector3D &wo) const {
    return (kd * cd * invPI);
}

RGBColor Lambertian::sample_f(const ShadeInfo &sr, Vector3D &wi,
                              const Vector3D &wo) const {
    // stub function
    return (RGBColor());
}

float clamp_kd(float kd) {
    if (kd > 1) {
        return 1.0;
    } else if (kd < 0) {
        return 0.0;
    } else {
        return kd;
    }
}