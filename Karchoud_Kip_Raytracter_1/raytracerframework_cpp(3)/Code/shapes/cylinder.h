#ifndef CYLINDER_H
#define CYLINDER_H

#include "../object.h"

class Cylinder: public Object
{
    public:
        Cylinder(Point const &pos, double radius, double height);

        virtual Hit insersect(Ray const &ray);

        Point const position;
        double const r;
        double const h;


};

#endif // CYLINDER_H

