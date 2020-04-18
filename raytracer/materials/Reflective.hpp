#pragma once

/**
   This file declares the Reflective class which models ambient, diffuse and
   specular direct illumination as well as reflections
*/

#include "Phong.hpp"

class PerfectSpecular;

// from chapter 25 of Ray Tracing from the Ground Up
class Reflective : public Phong {
   protected:
    PerfectSpecular *reflective_brdf;

   public:
    // Constructors.
    Reflective();
    Reflective(Lambertian *a, Lambertian *d, GlossySpecular *s,
               PerfectSpecular *r);

    // Copy constuctor and assignment operator.
    Reflective(const Reflective &other);
    Reflective &operator=(const Reflective &other);

    // Desctructor.
    virtual ~Reflective();

    void set_kr(float kr);
    void set_cr(RGBColor cr);

    virtual RGBColor shade(const ShadeInfo &sinfo) const;
};
