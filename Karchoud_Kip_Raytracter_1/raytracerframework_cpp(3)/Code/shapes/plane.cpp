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
//    double denum = N.dot(ray.D);
//    if(denum < 0.000001 && denum>-0.000001) return Hit::NO_HIT();

//    double t = ((pos - ray.O).dot(N)) / denum;
//    if (denum > 0.000001) {

//        return Hit(t, N);
//    }
//    return Hit::NO_HIT();
     double denom = N.dot(ray.D);
        if (fabs(denom) > 0.000001) {
            double temp = (pos-ray.O).dot(N);
            double t = (temp / denom);
            if(t<0)return Hit::NO_HIT();
            if(t > 0.000001) return Hit(t, N);
        }else{
            return Hit::NO_HIT();
        }


}

Plane::Plane(Point const &pos, Vector normal)
:
    pos(pos),
    normal(normal)

{}

