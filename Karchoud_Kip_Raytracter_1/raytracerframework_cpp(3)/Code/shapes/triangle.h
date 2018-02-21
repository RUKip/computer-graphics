#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "../object.h"

class Triangle: public Object
{
    public:
        Triangle(Point const &pos1, Point const &pos2, Point const &pos3);

        virtual Hit intersect(Ray const &ray);

        Point const pos1;
        Point const pos2;
        Point const pos3;
};

#endif
