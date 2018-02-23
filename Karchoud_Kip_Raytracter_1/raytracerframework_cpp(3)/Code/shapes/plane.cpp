#include "plane.h"

#include <cmath>
#include <iostream>

using namespace std;
Hit Plane::intersect(Ray const &ray)
{

    //https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
    //infinite plane

    //Direction
    Vector L = (ray.O - pos);

    //normalized normal
    Vector N = normal.normalized();
    double denum = L.dot(N);
    double t = ((pos - ray.O).dot(N)) / denum;
     if (denum > 0.000001) {

        return Hit(t, N);
     }


     if (t < 0) return Hit::NO_HIT();

}

Plane::Plane(Point const &pos, Vector normal)
:
    pos(pos),
    normal(normal)

{}

