#include "mesh.h"

#include <limits>
#include <cmath>
#include <iostream>

using namespace std;
Hit Mesh::intersect(Ray const &ray)
{
    double smallestT = std::numeric_limits<double>::max();
    Hit smallestHit = Hit::NO_HIT();
    for(Triangle triangle : triangles){
        Hit hit = triangle.intersect(ray);
        if(hit.t){
            if(hit.t<smallestT) smallestHit = hit;
        }
    }
    if(smallestT == std::numeric_limits<double>::max()) return Hit::NO_HIT();
    return smallestHit;
}

Mesh::Mesh(vector<Triangle> &triangles)
:
    triangles(triangles)
{}

