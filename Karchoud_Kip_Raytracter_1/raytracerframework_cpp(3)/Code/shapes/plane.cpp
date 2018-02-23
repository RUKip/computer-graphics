#include "plane.h"

#include <cmath>
#include <iostream>

using namespace std;
Hit Plane::intersect(Ray const &ray)
{

    //https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
    //infinite plane

    //normalized normal
    Vector N = normal.normalized();
    double denom = N.dot(ray.D);
    if (denom > 0.000001 || denom < -0.00001) {
        double temp = (pos-ray.O).dot(N);
        double t = (temp / denom);
        if(t<0)return Hit::NO_HIT();
        if(t > 0.000001) return Hit(t, N);
    }    
    return Hit::NO_HIT();


}

Plane::Plane(Point const &pos, Vector normal)
:
    pos(pos),
    normal(normal)

{}

