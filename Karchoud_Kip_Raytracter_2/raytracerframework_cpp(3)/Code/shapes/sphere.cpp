#include "sphere.h"

#include <cmath>
#include <iostream>
#include <math.h>

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
    Vector N = (hitPoint - position).normalized();

    return Hit(t,N);
}

Point Sphere::rotateUV(Point hit){
    Point b = cos(rotationAngle)*hit + sin(rotationAngle)*(rotationAxis*hit)+(rotationAxis*hit)*(1-cos(rotationAngle))*rotationAxis;

    //transform to cartesian, https://math.stackexchange.com/questions/1019910/rotation-matrix-in-spherical-coordinates
    //double angle1 = atan(b.y/b.x);
    //double angle2 = atan((sqrt(pow(b.x,2)+pow(b.y,2)))/b.z);
    //return Point(sin(angle2)*cos(angle1), sin(angle2)*sin(angle1), cos(angle2));

    //another transformation to cartesian??, http://mathworld.wolfram.com/SphericalCoordinates.html
    double r = sqrt(pow(b.x,2)+pow(b.y,2)+pow(b.z,2));
    double angle1 = atan(b.y/b.x);
    double angle2 = acos(b.z/r);
    double x = r*cos(angle1)*sin(angle2);
    double y = r*sin(angle1)*sin(angle2);
    double z = r*cos(angle2);
    return Point(x, y, z);

}

Vector Sphere::getTextureCoordinates(Point hit){
    hit = (hit - position);
    hit.normalize();
    if(rotationAngle) hit = rotateUV(hit);
    double u = 0.5 + atan2(hit.y, hit.x)/(2*M_PI);
    double v = 1 - (acos(hit.z)/M_PI);
    return Vector(u,v);
}

Sphere::Sphere(Point const &pos, double radius)
:
    position(pos),
    r(radius)
{}
