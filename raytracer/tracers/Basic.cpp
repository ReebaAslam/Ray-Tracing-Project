#include "Basic.hpp"
#include "../materials/Material.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"

Basic::Basic(World *world) : Tracer(world) {}

Basic::Basic(const Basic &tracer) : Tracer(tracer) {}

Basic &Basic::operator=(const Basic &tracer) {
    if (this == &tracer) {
        return (*this);
    }

    Tracer::operator=(tracer);
    return (*this);
}

RGBColor Basic::trace_ray(const Ray &ray) const {
    ShadeInfo sinfo(world->hit_objects(ray));
    float weight = ray.w;  // ray weight for the pixel.

    if (sinfo.hit) {
        sinfo.ray = ray;
        return (weight * sinfo.material_ptr->shade(sinfo));
    } else {
        return (weight * world->bg_color);
    }
}

RGBColor Basic::trace_ray_raw(const Ray &ray) const {
    ShadeInfo sinfo(world->hit_objects_raw(ray));
    float weight = ray.w;  // ray weight for the pixel.

    if (sinfo.hit) {
        sinfo.ray = ray;
        return (weight * sinfo.material_ptr->shade(sinfo));
    } else {
        return (weight * world->bg_color);
    }
}

RGBColor Basic::trace_ray(const Ray ray, const int depth) const {
    ShadeInfo sinfo(world->hit_objects(ray));
    float weight = ray.w;  // ray weight for the pixel.

    if (sinfo.hit) {
        sinfo.ray = ray;
        return (weight * sinfo.material_ptr->shade(sinfo));
    } else {
        return (weight * world->bg_color);
    }
}