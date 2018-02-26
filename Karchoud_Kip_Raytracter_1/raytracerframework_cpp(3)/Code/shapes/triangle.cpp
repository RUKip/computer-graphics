#include "triangle.h"

#include <cmath>
#include <iostream>

using namespace std;
Hit Triangle::intersect(Ray const &ray)
{

    //https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm, for orignal code and used intersection algorithm
    Vector h, s, q;
    double a,f,u,v;
    Vector edge1 = pos2 - pos1;
    Vector edge2 = pos3 - pos1;
    Vector N = (edge1.cross(edge2)).normalized();
    h = (ray.D).cross(edge2);
    a = edge1.dot(h);
    if (a<0.000001 && a>-0.000001) return Hit::NO_HIT(); //ray is parallel to triangle
    f = 1/a;
    s = ray.O - pos1;
    u = f * (s.dot(h));
    if (u < 0.0 || u > 1.0) return Hit::NO_HIT();
    q = s.cross(edge1);
    v = f*((ray.D).dot(q));
    if (v < 0.0 || u + v > 1.0) return Hit::NO_HIT();

    double t = f * edge2.dot(q);
    if (t > 0.000001){ //rays intersect with triangle
        Vector hitPoint = ray.O + ray.D * t; //dont really need hitpoint, but kept for testing purposes
        return Hit(t, N);
    }
    return Hit::NO_HIT();
}

Triangle::Triangle(Point const &pos1, Point const &pos2, Point const &pos3)
:
    pos1(pos1),
    pos2(pos2),
    pos3(pos3)
{}

