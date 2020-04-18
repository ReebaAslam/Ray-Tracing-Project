#pragma once

/**
   This file declares the Glossy Specular class that results in specular
   highlights.

*/

#include "../utilities/RGBColor.hpp"
#include "brdf.hpp"

// from chapter 15 of Ray Tracing from the Ground Up
class GlossySpecular : public BRDF {
   protected:
    float ks;     // specular coefficient
    RGBColor cs;  // specular color
    float e;      // specular exponent
   public:
    // Constructors
    GlossySpecular();
    GlossySpecular(float ks, RGBColor cs, float e);

    // Copy constructor and assignment operator
    GlossySpecular(const GlossySpecular &brdf);
    GlossySpecular &operator=(const GlossySpecular &other);

    // Destructor
    virtual ~GlossySpecular() = default;

    void set_ks(float ks);
    void set_cs(RGBColor cs);
    void set_e(float e);

    virtual RGBColor rho(const ShadeInfo &sr, const Vector3D &wo) const;

    virtual RGBColor f(const ShadeInfo &sr, const Vector3D &wi,
                       const Vector3D &wo) const;

    virtual RGBColor sample_f(const ShadeInfo &sr, Vector3D &wi,
                              const Vector3D &wo) const;
};