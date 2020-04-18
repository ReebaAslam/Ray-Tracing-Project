#pragma once

/**
   This file declares the Matte class which models perfect diffuse reflection
   with ambient and diffuse shading.
*/

#include "Material.hpp"

class Lambertian;

// from chapter 14 of Ray Tracing from the Ground Up
class Matte : public Material {
   protected:
    Lambertian *ambient_brdf;
    Lambertian *diffuse_brdf;

   public:
    // Constructors.
    Matte();
    Matte(Lambertian *a, Lambertian *d);

    // Copy constuctor and assignment operator.
    Matte(const Matte &other);
    Matte &operator=(const Matte &other);

    // Desctructor.
    virtual ~Matte();

    void set_ka(float ka);
    void set_kd(float kd);
    void set_cd(RGBColor c);
    
    virtual RGBColor shade(const ShadeInfo &sinfo) const override;
};
