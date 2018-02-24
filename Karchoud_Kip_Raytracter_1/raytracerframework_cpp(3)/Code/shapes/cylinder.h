#ifndef CYLINDER_H_
#define CYLINDER_H_

#include "../object.h"

class Cylinder: public Object
{
    public:
        Cylinder(Point const &pos, Vector direction, double radius);

        virtual Hit intersect(Ray const &ray);

        Point const position;
        double const r;
        Vector const direction;
};

#endif //CYLINDER
