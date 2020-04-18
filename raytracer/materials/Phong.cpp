#include "Phong.hpp"
#include "../brdf/GlossySpecular.hpp"
#include "../brdf/lambertian.hpp"
#include "../lights/Light.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"

// from chapter 15 of Ray Tracing from the Ground Up
Phong::Phong()
    : ambient_brdf(new Lambertian()),
      diffuse_brdf(new Lambertian()),
      specular_brdf(new GlossySpecular()){};

Phong::Phong(Lambertian *a, Lambertian *d, GlossySpecular *s)
    : ambient_brdf(a), diffuse_brdf(d), specular_brdf(s){};

Phong::Phong(const Phong &other) : Material(other) {
    *ambient_brdf = *(other.ambient_brdf);
    *diffuse_brdf = *(other.diffuse_brdf);
    *specular_brdf = *(other.specular_brdf);
};

Phong &Phong::operator=(const Phong &other) {
    if (this == &other) {
        return (*this);
    }

    Material::operator=(other);
    *ambient_brdf = *(other.ambient_brdf);
    *diffuse_brdf = *(other.diffuse_brdf);
    *specular_brdf = *(other.specular_brdf);
    return (*this);
}

Phong::~Phong() {
    if (ambient_brdf) {
        delete ambient_brdf;
        ambient_brdf = NULL;
    }

    if (diffuse_brdf) {
        delete diffuse_brdf;
        diffuse_brdf = NULL;
    }

    if (specular_brdf) {
        delete specular_brdf;
        specular_brdf = NULL;
    }
}

// from chapter 15 of Ray Tracing from the Ground Up
void Phong::set_ka(float ka) { ambient_brdf->set_kd(ka); }

// from chapter 15 of Ray Tracing from the Ground Up
void Phong::set_kd(float kd) { diffuse_brdf->set_kd(kd); }

// from chapter 15 of Ray Tracing from the Ground Up
void Phong::set_ks(float ks) { specular_brdf->set_ks(ks); }

// from chapter 15 of Ray Tracing from the Ground Up
void Phong::set_cd(RGBColor cd) {
    ambient_brdf->set_cd(cd);
    diffuse_brdf->set_cd(cd);
}

// from chapter 15 of Ray Tracing from the Ground Up
void Phong::set_cs(RGBColor cs) { specular_brdf->set_cs(cs); }

// from chapter 15 of Ray Tracing from the Ground Up
void Phong::set_exp(float e) { specular_brdf->set_e(e); }

// from chapter 15 and 16 of Ray Tracing from the Ground Up
RGBColor Phong::shade(const ShadeInfo &sinfo) const {
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
                L += (diffuse_brdf->f(sinfo, wi, wo) +
                      specular_brdf->f(sinfo, wo, wi)) *
                     sinfo.w->lights[i]->getL(sr) * ndotwi;
            }
        }
    }

    return (L);
}
