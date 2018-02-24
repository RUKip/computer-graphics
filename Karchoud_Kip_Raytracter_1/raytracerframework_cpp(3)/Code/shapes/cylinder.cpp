#include "cylinder.h"

#include <cmath>
#include <iostream>

using namespace std;

Hit Cylinder::intersect(Ray const &ray)
{
    //intersection calculation, original from http://mrl.nyu.edu/~dzorin/rend05/lecture2.pdf


    //TODO: ^2, should be a double?
    Vector temp = (ray.D - ((ray.D.dot(direction))*direction));
    Vector diffVector = ray.O - position;
    double A = temp.dot(temp);
    double B = 2*(temp.dot((diffVector-(diffVector.dot(direction)*direction))));
    Vector temp2 = (diffVector - (diffVector.dot(direction)*direction));
    double C = (temp2.dot(temp2)) - (r*r);

    double discriminant = sqrt(B*B-4*A*C);
    double t1 = (-1*B - discriminant) / (2*A); //nearest?
    double t2 = (-1*B + discriminant) / (2*A);

    cout << "t1: " << t1 << " and t2: " << t2 << "\n";

    return Hit::NO_HIT();

}

Cylinder::Cylinder(Point const &pos, Vector direction, double radius) //TODO: add height to make it finite
:
    position(pos),
    r(radius),
    direction(direction)
{}
