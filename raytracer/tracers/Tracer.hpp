#pragma once

/**
   This file declares the Tracer class which is an abstract class for concrete
   tracers to inherit from.
*/

class World;
class RGBColor;
class Ray;

class Tracer {
   protected:
    World *world;

   public:
    Tracer();
    Tracer(World *world);

    // Copy constructor and assignment operator
    Tracer(const Tracer &tracer);
    Tracer &operator=(const Tracer &other);

    // Destructor
    virtual ~Tracer();

    virtual RGBColor trace_ray(const Ray &ray) const = 0;

    virtual RGBColor trace_ray(const Ray ray, const int depth) const = 0;

    virtual RGBColor trace_ray_raw(const Ray &ray) const = 0;
};