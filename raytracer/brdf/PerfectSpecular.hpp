#pragma once

/**
   This file declares the Glossy Specular class that results in perfect mirror
   reflection.

*/

#include "../utilities/RGBColor.hpp"
#include "brdf.hpp"

// from chapter 24 of Ray Tracing from the Ground Up
class PerfectSpecular : public BRDF {
   protected:
    float kr;     // reflection coefficient
    RGBColor cr;  // reflection color
   public:
    // Constructors
    PerfectSpecular();
    PerfectSpecular(float kr, RGBColor cr);

    // Copy constructor and assignment operator
    PerfectSpecular(const PerfectSpecular &brdf);
    PerfectSpecular &operator=(const PerfectSpecular &other);

    // Destructor
    virtual ~PerfectSpecular() = default;

    void set_kr(float kr);
    void set_cr(RGBColor cr);

    virtual RGBColor rho(const ShadeInfo &sr, const Vector3D &wo) const;

    virtual RGBColor f(const ShadeInfo &sr, const Vector3D &wi,
                       const Vector3D &wo) const;

    virtual RGBColor sample_f(const ShadeInfo &sr, Vector3D &wi,
                              const Vector3D &wo) const;
};