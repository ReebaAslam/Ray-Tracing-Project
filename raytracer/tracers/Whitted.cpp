#include "Whitted.hpp"
#include "../materials/Material.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"

Whitted::Whitted(World *world) : Tracer(world) {}

Whitted::Whitted(const Whitted &tracer) : Tracer(tracer) {}

Whitted &Whitted::operator=(const Whitted &tracer) {
    if (this == &tracer) {
        return (*this);
    }

    Tracer::operator=(tracer);
    return (*this);
}

// from chapter 24 of Ray Tracing from the Ground Up
RGBColor Whitted::trace_ray(const Ray ray, const int depth) const {
    if (depth > world->vplane.max_depth) {
        return (black);
    } else {
        ShadeInfo sinfo(world->hit_objects(ray));

        if (sinfo.hit) {
            sinfo.depth = depth;
            sinfo.ray = ray;

            return (sinfo.material_ptr->shade(sinfo));
        } else {
            return (world->bg_color);
        }
    }
}

RGBColor Whitted::trace_ray(const Ray &ray) const {
    // function not relevant for this tracer
    return (black);
}

RGBColor Whitted::trace_ray_raw(const Ray &ray) const {
    // function not relevant for this tracer
    return (black);
}
