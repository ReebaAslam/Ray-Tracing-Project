#pragma once

/**
   This file declares the Basic class which is the basic tracer
   used for rendering the scene
*/

#include "Tracer.hpp"

class Basic : public Tracer {
   public:
    Basic() = default;
    Basic(World *world);

    // Copy constuctor and assignment operator.
    Basic(const Basic &tracer);
    Basic &operator=(const Basic &tracer);

    virtual ~Basic() = default;

    virtual RGBColor trace_ray(const Ray &ray) const override;

    virtual RGBColor trace_ray(const Ray ray, const int depth) const override;

    virtual RGBColor trace_ray_raw(const Ray &ray) const override;
};