#pragma once

/**
   This file declares the Lambertian class which represents perfect diffuse
   reflection.

*/

#include "../utilities/RGBColor.hpp"
#include "brdf.hpp"

// from chapter 13 of Ray Tracing from the Ground Up
class Lambertian : public BRDF {
   protected:
    float kd;     // diffuse reflection coefficient
    RGBColor cd;  // diffuse color
   public:
    // Constructors
    Lambertian();
    Lambertian(float kd, RGBColor cd);

    // Copy constructor and assignment operator
    Lambertian(const Lambertian &brdf);
    Lambertian &operator=(const Lambertian &other);

    // Destructor
    virtual ~Lambertian() = default;

    void set_kd(float kd);
    void set_cd(RGBColor cd);

    virtual RGBColor rho(const ShadeInfo &sr, const Vector3D &wo) const;

    virtual RGBColor f(const ShadeInfo &sr, const Vector3D &wi,
                       const Vector3D &wo) const;

    virtual RGBColor sample_f(const ShadeInfo &sr, Vector3D &wi,
                              const Vector3D &wo) const;
};
float clamp_kd(float kd);