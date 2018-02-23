#include "plane.h"

#include <cmath>
#include <iostream>

using namespace std;
Hit Plane::intersect(Ray const &ray)
{

    //https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
    //infinite plane

    Vector L = (ray.D - pos);

     if (L.dot(normal) > 1e-6) {
        double t = ((pos - ray.O).dot(normal)) / L.dot(normal);
        return Hit(t, normal);
     }
    return Hit::NO_HIT();
}

Plane::Plane(Point const &pos, Vector normal)
:
    pos(pos),
    normal(normal)

{}

