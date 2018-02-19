#include "sphere.h"

#include <cmath>

using namespace std;

Hit Sphere::intersect(Ray const &ray)
{
    /****************************************************
    * RT1.1: INTERSECTION CALCULATION
    *
    * Given: ray, position, r
    * Sought: intersects? if true: *t
    *
    * Insert calculation of ray/sphere intersection here.
    *
    * You have the sphere's center (C) and radius (r) as well as
    * the ray's origin (ray.O) and direction (ray.D).
    *
    * If the ray does not intersect the sphere, return false.
    * Otherwise, return true and place the distance of the
    * intersection point from the ray origin in *t (see example).
    ****************************************************/

    //intersection calculation, used https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection for helping with intersection calculation, TODO: is fine right?

    //TODO: not working but fun result

    Vector OC = (position - ray.O).normalized();
    double DOnOC = OC.dot(ray.D);
    if(DOnOC<0) return Hit::NO_HIT(); //there is a hit behind the camera/eye so no hit //TODO: what if we want to implement reflection? Ray continues to bounce behind eye and back?
    double d = sqrt(OC.dot(OC) - DOnOC*DOnOC);
    if(d>r) return Hit::NO_HIT(); //distance between direction and circle origin is larger then radiance, so no hit
    double lenHitC = sqrt(r*r - d*d); //length first hitpoint to sphere origin
    double lenHitO1 = DOnOC - lenHitC; //lenght of first hit //TODO: do we want to return both intersection points?? or only that of the closest?
    double lenHitO2 = DOnOC - lenHitC; //lenght of second hit. //TODO: do we ever need this?
    double t = lenHitO1;

    //original code, remove later TODO:
//    Vector OC = (position - ray.O).normalized();
//    if (OC.dot(ray.D) < 0.999) {
//        return Hit::NO_HIT();
//    }
//    double t = 1000;

    /****************************************************
    * RT1.2: NORMAL CALCULATION
    *
    * Given: t, C, r
    * Sought: N
    *
    * Insert calculation of the sphere's normal at the intersection point.
    ****************************************************/

    Vector N /* = ... */;

    return Hit(t,N);
}

Sphere::Sphere(Point const &pos, double radius)
:
    position(pos),
    r(radius)
{}
