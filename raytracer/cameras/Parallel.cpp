#include "Parallel.hpp"
#include <iostream>

Parallel::Parallel() : dir(0, 0, -1) {}

Parallel::Parallel(float c) : dir(c) { dir.normalize(); }

Parallel::Parallel(float x, float y, float z) : dir(x, y, z) { dir.normalize(); }

Parallel::Parallel(const Vector3D &d) : dir(d) { dir.normalize(); }

Parallel::Parallel(const Parallel &camera) : Camera(camera), dir(camera.dir) {}

Parallel &Parallel::operator=(const Parallel &other) {
    if (this == &other) {
        return (*this);
    }

    Camera::operator=(other);       // only relevant if assignment operator is defined
    dir = other.dir;
    return (*this);
}

Vector3D Parallel::get_direction(const Point3D &p) const {
    return dir;
}