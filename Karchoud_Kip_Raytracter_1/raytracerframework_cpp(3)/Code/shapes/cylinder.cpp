#include "cylinder.h"

#include <cmath>
#include <iostream>

using namespace std;

Hit Cylinder::intersect(Ray const &ray)
{

    //https://github.com/spinatelli/raytracer -> cylinder is dan wel infinite
    //https://github.com/DanielsWrath/ComputerGraphics/tree/master/Raytracer-1/Raytracer -> plane is hier defined als een cube/quad.
    //intersection calculation


}

Cylinder::Cylinder(Point const &pos, double radius, double height)
:
    position(pos),
    r(radius),
    height(height)
{}
