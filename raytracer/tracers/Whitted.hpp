#pragma once

/**
   This file declares the Whitted class which is used for implementing
   reflections.
*/

#include "Tracer.hpp"

class Whitted : public Tracer {
   public:
    Whitted() = default;
    Whitted(World *world);

    // Copy constuctor and assignment operator.
    Whitted(const Whitted &tracer);
    Whitted &operator=(const Whitted &tracer);

    virtual ~Whitted() = default;

    virtual RGBColor trace_ray(const Ray &ray) const override;

    virtual RGBColor trace_ray(const Ray ray, const int depth) const override;

    virtual RGBColor trace_ray_raw(const Ray &ray) const override;
};