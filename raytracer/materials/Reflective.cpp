#include "Reflective.hpp"
#include "../brdf/PerfectSpecular.hpp"
#include "../lights/Light.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"
#include "../tracers/Tracer.hpp"

// from chapter 24 of Ray Tracing from the Ground Up
Reflective::Reflective()
    : reflective_brdf (new PerfectSpecular) {};

Reflective::Reflective(Lambertian *a, Lambertian *d, GlossySpecular *s, PerfectSpecular *r)
    : Phong(a, d, s), reflective_brdf(r) {};

Reflective::Reflective(const Reflective &other) : Phong(other) {
    *reflective_brdf = *(other.reflective_brdf);
};

Reflective &Reflective::operator=(const Reflective &other) {
    if (this == &other) {
        return (*this);
    }

    Phong::operator=(other);
    *reflective_brdf = *(other.reflective_brdf);
    return (*this);
}

Reflective::~Reflective() {
    if (reflective_brdf) {
        delete reflective_brdf;
        reflective_brdf = NULL;
    }

}

void Reflective::set_kr(float kr) { reflective_brdf->set_kr(kr); }

void Reflective::set_cr(RGBColor cr) {
    reflective_brdf->set_cr(cr);
}

// from chapter 24 of Ray Tracing from the Ground Up
RGBColor Reflective::shade(const ShadeInfo &sinfo) const {
    RGBColor L(Phong::shade(sinfo));        // direct illumination

    Vector3D wo = -sinfo.ray.d;
    Vector3D wi;
    RGBColor fr = reflective_brdf->sample_f(sinfo, wi, wo);
    Ray reflected_ray(sinfo.hit_point, wi);

    L += fr * sinfo.w->tracer->trace_ray(reflected_ray, sinfo.depth + 1) * (sinfo.normal * wi);

    return (L);
}
