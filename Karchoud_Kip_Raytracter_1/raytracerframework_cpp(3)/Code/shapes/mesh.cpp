#include "mesh.h"

#include <limits>
#include <cmath>
#include <math.h>
#include <iostream>

using namespace std;
Hit Mesh::intersect(Ray const &ray)
{
    double smallestT = std::numeric_limits<double>::max();
    Hit smallestHit = Hit::NO_HIT();
    for(ObjectPtr trianglePtr : triangles){
        Hit hit = trianglePtr->intersect(ray);
        if(!isnan(hit.t)){
            if(hit.t<smallestT){
                smallestHit = hit;
                smallestT = hit.t;
            }
        }
    }
    if(smallestT == std::numeric_limits<double>::max()) return Hit::NO_HIT();
    return smallestHit;
}

Mesh::Mesh(string model, double scaling, double xTransform, double yTransform, double zTransform)
{
    OBJLoader loader(model);
    //loader.unitize(); //TODO: unitize here, if implemented
    vector<Vertex> vertices = loader.vertex_data();
    for(unsigned int nr_vertex=0; nr_vertex<(loader.numTriangles()*3); nr_vertex+=3){
        Vertex v1 = vertices[nr_vertex];
        Point point1((scaling*v1.x)+xTransform, (scaling*v1.y)+yTransform, (scaling*v1.z)+zTransform);
        Vertex v2 = vertices[nr_vertex+1];
        Point point2((scaling*v2.x)+xTransform, (scaling*v2.y)+yTransform, (scaling*v2.z)+zTransform);
        Vertex v3 = vertices[nr_vertex+2];
        Point point3((scaling*v3.x)+xTransform, (scaling*v3.y)+yTransform, (scaling*v3.z)+zTransform);
        triangles.push_back(ObjectPtr(new Triangle(point1, point2, point3)));
    }
}

