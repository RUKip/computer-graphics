#include "cylinder.h"

#include <cmath>
#include <iostream>

using namespace std;

Hit Cylinder::intersect(Ray const &ray)
{
    /****************************************************
    * RT1.1: INTERSECTION CALCULATION
    *
    * Given: ray, position, r and h
    * Sought: intersects? if true: *t
    *
    * Insert calculation of ray/cylinder intersection here.
    *
    * You have the cylinder's center (C) and radius (r) as well as
    * the ray's origin (ray.O) and direction (ray.D).
    *
    * If the ray does not intersect the sphere, return false.
    * Otherwise, return true and place the distance of the
    * intersection point from the ray origin in *t (see example).
    *
    * ray       = q = p +vt
    * cylinder  = (q-pa-(va,q-pa)va)^2-r^2
     ****************************************************/

    //intersection calculation http://mrl.nyu.edu/~dzorin/rend05/lecture2.pdf


    /****************************************************
    * RT1.2: NORMAL CALCULATION
    *
    * Given: t, C, r
    * Sought: N
    *
    * Insert calculation of the cylinder's normal at the intersection point.
    ****************************************************/


}

Sphere::Sphere(Point const &pos, double radius, double height)
:
    position(pos),
    r(radius),
    h(height)
{}
