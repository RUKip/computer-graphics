#include "sphere.h"

#include <cmath>
#include <iostream>

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

    //intersection calculation
    Vector L  = (ray.O - position);
    double b = 2*(ray.D.dot(L));
    double c = L.dot(L) - r*r;
    double discriminant = pow(b,2) - 4*c;
    if(discriminant<0) return Hit::NO_HIT();
    double hit1 = (-b + sqrt(discriminant))/2;
    double hit2 = (-b - sqrt(discriminant))/2;
    double t = min(hit1, hit2);
    if(t<0) return Hit::NO_HIT();

    /****************************************************
    * RT1.2: NORMAL CALCULATION
    *
    * Given: t, C, r
    * Sought: N
    *
    * Insert calculation of the sphere's normal at the intersection point.
    ****************************************************/

    Vector hitPoint = ray.O + t*ray.D;
    Vector N = (hitPoint - position).normalized(); //TODO: why normalized??

    return Hit(t,N);
}

Sphere::Sphere(Point const &pos, double radius)
:
    position(pos),
    r(radius)
{}
