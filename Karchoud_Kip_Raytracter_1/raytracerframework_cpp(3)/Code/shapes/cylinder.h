#ifndef CYLINDER_H_
#define CYLINDER_H_

#include "../object.h"

class Cylinder: public Object
{
    public:
        Cylinder(Point const &pos, double radius, double height);

        virtual Hit intersect(Ray const &ray);

        Point const position;
        double const r;
        double const height;
};

#endif //CYLINDER
