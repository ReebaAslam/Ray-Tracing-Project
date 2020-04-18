#pragma once

/**
   This file declares the BRDF class which is an abstract class for concrete
   BRDFs to inherit from. A BRDF implements basic reflection mechanisms.

*/

#include "../utilities/Vector3D.hpp"
class Vector3D;
class Sampler;
class RGBColor;
class ShadeInfo;

class BRDF {
   protected:
    Sampler *sampler;

   public:
    // Constructors
    BRDF() = default;

    // Copy constructor and assignment operator
    BRDF(const BRDF &brdf) = default;
    BRDF &operator=(const BRDF &other) = default;

    // Destructor
    virtual ~BRDF() = default;

    virtual RGBColor rho(const ShadeInfo &sr,
                         const Vector3D &wo) const = 0;  // returns reflectance

    virtual RGBColor f(const ShadeInfo &sr, const Vector3D &wi,
                       const Vector3D &wo)
        const = 0;  // returns constant of proportionality (BRDF)

    virtual RGBColor sample_f(const ShadeInfo &sr, Vector3D &wi,
                              const Vector3D &wo)
        const = 0;  // for computing direciton of reflected rays
};
// from chapter 13 of Ray Tracing from the Ground Up