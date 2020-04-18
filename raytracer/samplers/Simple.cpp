#include "Simple.hpp"
#include <math.h>
#include <iostream>
#include "../cameras/Camera.hpp"
#include "../utilities/Ray.hpp"
#include "../world/ViewPlane.hpp"

Simple::Simple(Camera *c_ptr, ViewPlane *v_ptr) : Sampler(c_ptr, v_ptr) {
    if (viewplane_ptr->top_left.z == viewplane_ptr->bottom_right.z) {
        diff = viewplane_ptr->bottom_right - viewplane_ptr->top_left;
    }
}

Simple::Simple(const Simple &camera) : Sampler(camera) {}

Simple &Simple::operator=(const Simple &other) {
    if (this == &other) {
        return (*this);
    }

    Sampler::operator=(other);
    return (*this);
}

std::vector<Ray> Simple::get_rays(int px, int py) const {
    // Shoot a ray of weight 1 through the center of the pixel.
    std::vector<Ray> shoot;
    Point3D origin;
    Vector3D temp(((double)px /(double) viewplane_ptr->hres) * diff.x,
                      ((double)py / (double)viewplane_ptr->vres) * diff.y, 0);
    origin = viewplane_ptr->top_left + temp;
    Vector3D dir = camera_ptr->get_direction(origin);
    shoot.push_back(Ray(origin, dir));
    return shoot;
}
