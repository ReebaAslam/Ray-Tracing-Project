#pragma once

/**
   This file declares the Phong class which models specular reflection
   with ambient and diffuse shading.
*/

#include "Material.hpp"

class Lambertian;
class GlossySpecular;

// from chapter 15 of Ray Tracing from the Ground Up
class Phong : public Material {
   protected:
    Lambertian *ambient_brdf;
    Lambertian *diffuse_brdf;
    GlossySpecular *specular_brdf;

   public:
    // Constructors.
    Phong();
    Phong(Lambertian *a, Lambertian *d, GlossySpecular *s);

    // Copy constuctor and assignment operator.
    Phong(const Phong &other);
    Phong &operator=(const Phong &other);

    // Desctructor.
    virtual ~Phong();

    void set_ka(float ka);
    void set_kd(float kd);
    void set_ks(float ks);
    void set_cd(RGBColor cd);
    void set_cs(RGBColor cs);
    void set_exp(float e);

    virtual RGBColor shade(const ShadeInfo &sinfo) const override;
};
