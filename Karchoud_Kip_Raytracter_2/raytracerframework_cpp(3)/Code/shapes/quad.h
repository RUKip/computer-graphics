#ifndef QUAD_H_
#define QUAD_H_

#include "../object.h"

class Quad: public Object
{
    public:
        Quad(Point const &pos1, Point const &pos2, Point const &pos3, Point const &pos4);

        virtual Hit intersect(Ray const &ray);

        Point const pos1;
        Point const pos2;
        Point const pos3;
        Point const pos4;
};

#endif //Quad
