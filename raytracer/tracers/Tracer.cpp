#include "Tracer.hpp"
#include "../utilities/RGBColor.hpp"
#include "../world/World.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/Constants.hpp"

Tracer::Tracer() : world(NULL) {}

Tracer::Tracer(World *world) : world(world) {}

Tracer::Tracer(const Tracer &tracer) { *world = *(tracer.world); }

Tracer &Tracer::operator=(const Tracer &other) {
    if (this == &other) {
        return (*this);
    }

    *world = *(other.world);
    return (*this);
}

Tracer::~Tracer() {
    if (world) {
        delete world;
        world = NULL;
    }
}