#include "Matte.hpp"
#include "../brdf/lambertian.hpp"
#include "../lights/Light.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"

// from chapter 14 of Ray Tracing from the Ground Up
Matte::Matte()
    : ambient_brdf(new Lambertian()), diffuse_brdf(new Lambertian()){};

Matte::Matte(Lambertian *a, Lambertian *d) : ambient_brdf(a), diffuse_brdf(d){};

Matte::Matte(const Matte &other) : Material(other) {
    *ambient_brdf = *(other.ambient_brdf);
    *diffuse_brdf = *(other.diffuse_brdf);
};

Matte &Matte::operator=(const Matte &other) {
    if (this == &other) {
        return (*this);
    }

    Material::operator=(other);
    *ambient_brdf = *(other.ambient_brdf);
    *diffuse_brdf = *(other.diffuse_brdf);
    return (*this);
}

Matte::~Matte() {
    if (ambient_brdf) {
        delete ambient_brdf;
        ambient_brdf = NULL;
    }

    if (diffuse_brdf) {
        delete diffuse_brdf;
        diffuse_brdf = NULL;
    }
}

// from chapter 14 of Ray Tracing from the Ground Up
void Matte::set_ka(float ka) { ambient_brdf->set_kd(ka); }

// from chapter 14 of Ray Tracing from the Ground Up
void Matte::set_kd(float kd) { diffuse_brdf->set_kd(kd); }

// from chapter 14 of Ray Tracing from the Ground Up
void Matte::set_cd(RGBColor c) {
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}

// from chapter 14 and 16 of Ray Tracing from the Ground Up
RGBColor Matte::shade(const ShadeInfo &sinfo) const {
    Vector3D wo = -sinfo.ray.d;
    ShadeInfo sr(sinfo);
    RGBColor L =
        ambient_brdf->rho(sinfo, wo) * sinfo.w->ambient_light->getL(sr);
    int numLights = sinfo.w->lights.size();

    for (int i = 0; i < numLights; i++) {
        Vector3D wi = sinfo.w->lights[i]->getDirection(sr);
        float ndotwi = sinfo.normal * wi;

        if (ndotwi > 0.0) {
            bool in_shadow = false;

            if (sinfo.w->lights[i]->casts_shadows()) {
                Ray shadowRay(sinfo.hit_point, wi);
                in_shadow = sinfo.w->lights[i]->in_shadow(shadowRay, sinfo);
            }

            if (!in_shadow) {
                L += diffuse_brdf->f(sinfo, wi, wo) *
                     sinfo.w->lights[i]->getL(sr) * ndotwi;
            }
        }
    }

    return (L);
}