#include "quad.h"

#include <cmath>
#include <iostream>

using namespace std;
Hit Quad::intersect(Ray const &ray)
{

    //Assuming planar quads.. TODO: how to handle non planar quads?
    //same code as plane for intersection point
    //https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
    //infinite plane

    //normalized normal (same normal calculation as for triangle we are assuming planar quad)
    Vector edge1 = pos2 - pos1;
    Vector edge2 = pos3 - pos1;
    Vector N = (edge1.cross(edge2)).normalized();
    double denom = N.dot(ray.D);
    if (denom > 0.000001 || denom < -0.00001) {
        double temp = (pos1-ray.O).dot(N);
        double t = (temp / denom);
        if(t<0)return Hit::NO_HIT();
        if(t > 0.000001){
            Vector hitPoint = (t*ray.D) + ray.O;
            //check if hitpoint is to the left of each line in the polygon(this case quad) source: https://math.stackexchange.com/questions/1232773/is-the-point-on-the-left-or-the-right-of-the-vector-in-2d-space
            double s1 = ((pos2 - pos1).cross(hitPoint - pos1)).z;
            double s2 = ((pos3 - pos2).cross(hitPoint - pos2)).z;
            double s3 = ((pos4 - pos3).cross(hitPoint - pos3)).z;
            double s4 = ((pos1 - pos4).cross(hitPoint - pos4)).z;

            if(s1>0 && s2>0 && s3>0 && s4>0)    return Hit(t, N); //all to the same side of our quad so inside quad
            if(s1<0 && s2<0 && s3<0 && s4<0)    return Hit(t, N); //all to the same side of our quad so inside quad
        }
    }
    return Hit::NO_HIT();


}

Quad::Quad(Point const &pos1, Point const &pos2, Point const &pos3, Point const &pos4)
:
  pos1(pos1),
  pos2(pos2),
  pos3(pos3),
  pos4(pos4)

{}

