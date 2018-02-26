#ifndef MESH_H_
#define MESH_H_

#include "../object.h"
#include "triangle.h"
#include "../objloader.h"

using namespace std;

class Mesh: public Object
{
    public:
        Mesh(string path, double scaling, double xTransform, double yTransform, double zTransform);

        virtual Hit intersect(Ray const &ray);

        vector<ObjectPtr> triangles;
};

#endif
