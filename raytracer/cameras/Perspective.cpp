#include "Perspective.hpp"
#include "../utilities/Vector3D.hpp"

Perspective::Perspective() : pos(0.0) {}

Perspective::Perspective(float c) : pos(c) {}

Perspective::Perspective(float x, float y, float z) : pos(x, y, z) {}

Perspective::Perspective(const Point3D &pt) : pos(pt) {}

Perspective::Perspective(const Perspective &camera)
    : Camera(camera), pos(camera.pos) {}

Perspective &Perspective::operator=(const Perspective &other) {
    if (this == &other) {
        return (*this);
    }

    Camera::operator=(other);           // only relevant if assignment operator is defined in Camera class
    pos = other.pos;
    return (*this);
}

Vector3D Perspective::get_direction(const Point3D &p) const {
    // Get direction of projection for a point
    return (p - pos);
}