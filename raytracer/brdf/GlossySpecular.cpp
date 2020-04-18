#include "GlossySpecular.hpp"
#include <cmath>
#include "../utilities/Constants.hpp"
#include "../utilities/ShadeInfo.hpp"

float clamp_ks(float ks);

// from chapter 15 of Ray Tracing from the Ground Up
GlossySpecular::GlossySpecular() : ks(0.0), cs(0.0), e(0.0) {}

GlossySpecular::GlossySpecular(float ks, RGBColor cs, float e)
    : ks(clamp_ks(ks)), cs(cs), e(e) {}

GlossySpecular::GlossySpecular(const GlossySpecular &brdf)
    : ks(brdf.ks), cs(brdf.cs), e(brdf.e), BRDF(brdf) {}

GlossySpecular &GlossySpecular::operator=(const GlossySpecular &other) {
    if (this == &other) {
        return (*this);
    }

    BRDF::operator=(other);
    ks = other.ks;
    cs = other.cs;
    e = other.e;
    return (*this);
}

// from chapter 15 of Ray Tracing from the Ground Up
void GlossySpecular::set_cs(RGBColor cs) { this->cs = cs; }

// from chapter 15 of Ray Tracing from the Ground Up
void GlossySpecular::set_ks(float ks) { this->ks = clamp_ks(ks); }

// from chapter 15 of Ray Tracing from the Ground Up
void GlossySpecular::set_e(float e) { this->e = e; }

// from chapter 15 of Ray Tracing from the Ground Up
RGBColor GlossySpecular::rho(const ShadeInfo &sr, const Vector3D &wo) const {
    return (black);
}

// from chapter 15 of Ray Tracing from the Ground Up
RGBColor GlossySpecular::f(const ShadeInfo &sr, const Vector3D &wi,
                           const Vector3D &wo) const {
    RGBColor L;
    float ndotwi = sr.normal * wi;
    Vector3D r(-wi + 2.0 * sr.normal * ndotwi);  // reflected direction
    float rdotwo = r * wo;

    if (rdotwo > 0.0) {
        L = ks * pow(rdotwo, e) * cs;
    }

    return (L);
}

RGBColor GlossySpecular::sample_f(const ShadeInfo &sr, Vector3D &wi,
                              const Vector3D &wo) const {
    // stub function
    return (RGBColor());
}

float clamp_ks(float ks) {
    if (ks > 1) {
        return 1.0;
    } else if (ks < 0) {
        return 0.0;
    } else {
        return ks;
    }
}