#include "triangle.h"

#include <cmath>
#include <iostream>

using namespace std;
Hit Triangle::intersect(Ray const &ray)
{
    /* Your intersect calculation goes here */

    Vector N1 = pos1 - pos2;
    Vector N2 = pos3 - pos2;

    Vector N = (N1.cross(N2)).normalized();

    if(N.dot(ray.D)==0) return Hit::NO_HIT();
    double d = N.dot(pos1);
    double t = -1*(N.dot(ray.O) + d) / N.dot(ray.D);
    Vector hitPoint = ray.O+(t*ray.D);

    //cout << N;

    double rightsideCheck;
    //inside triangle?? (culling)
    Vector Edge1 = pos3 - pos2;
    Vector pointToHit1 = hitPoint - pos2;
    rightsideCheck =  N.dot(Edge1.cross(pointToHit1));
    if(rightsideCheck<0) return Hit::NO_HIT();
    Vector Edge2 = pos2 - pos1;
    Vector pointToHit2 = hitPoint - pos1;
    rightsideCheck = N.dot(Edge2.cross(pointToHit2));
    if(rightsideCheck<0) return Hit::NO_HIT();
    Vector Edge3 = pos1 - pos3;
    Vector pointToHit3 = hitPoint - pos3;               //TODO: rightside check always below 0 here... //check formula or check data
    rightsideCheck =  N.dot(Edge3.cross(pointToHit3));
    cout << rightsideCheck;

    if(rightsideCheck<0) return Hit::NO_HIT();
    cout << t;
    if(t<0) return Hit::NO_HIT();

    //double t = 0 /* = ... */;

    return Hit(t, N);
}

Triangle::Triangle(Point const &pos1, Point const &pos2, Point const &pos3)
:
    pos1(pos1),
    pos2(pos2),
    pos3(pos3)
{}

