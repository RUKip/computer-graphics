#ifndef MESH_H_
#define MESH_H_

#include "../object.h"
#include "triangle.h"
using std::vector;

class Mesh: public Object
{
    public:
        Mesh(vector<Triangle> &triangles);

        virtual Hit intersect(Ray const &ray);

        vector<Triangle> triangles;
};

#endif
