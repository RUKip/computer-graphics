#include "raytracer.h"

#include "image.h"
#include "light.h"
#include "material.h"
#include "triple.h"
#include "objloader.h"

// =============================================================================
// -- Include all your shapes here ---------------------------------------------
// =============================================================================

#include "shapes/sphere.h"
#include "shapes/triangle.h"
#include "shapes/mesh.h"
#include "shapes/plane.h"
#include "shapes/cylinder.h" //TODO: not implemented yet
#include "shapes/quad.h"

// =============================================================================
// -- End of shape includes ----------------------------------------------------
// =============================================================================

#include "json/json.h"

#include <exception>
#include <fstream>
#include <iostream>

using namespace std;        // no std:: required
using json = nlohmann::json;

bool Raytracer::parseObjectNode(json const &node)
{
    ObjectPtr obj = nullptr;

// =============================================================================
// -- Determine type and parse object parametrers ------------------------------
// =============================================================================

    if (node["type"] == "sphere")
    {
        Point pos(node["position"]);
        double radius = node["radius"];
        obj = ObjectPtr(new Sphere(pos, radius));
    }else if(node["type"] == "triangle")
    {
        Point pos1(node["pos1"]);
        Point pos2(node["pos2"]);
        Point pos3(node["pos3"]);
        obj = ObjectPtr(new Triangle(pos1, pos2, pos3));
    }else if(node["type"] == "mesh"){
      string model = node["model"];
      OBJLoader loader(model);
        //loader.unitize(); //TODO: unitize here, if implemented
        vector<Triangle*> triangles;
        vector<Vertex> vertices = loader.vertex_data();
        for(unsigned int nr_vertex=0; nr_vertex<(loader.numTriangles()*3); nr_vertex+=3){ //TODO: add a scaling factor to object
            double scalingFactor = 1;
            Vertex v1 = vertices[nr_vertex];
            Point point1(scalingFactor*v1.x, scalingFactor*v1.y, scalingFactor*v1.z);
            Vertex v2 = vertices[nr_vertex+1];
            Point point2(scalingFactor*v2.x, scalingFactor*v2.y, scalingFactor*v2.z);
            Vertex v3 = vertices[nr_vertex+2];
            Point point3(scalingFactor*v3.x, scalingFactor*v3.y, scalingFactor*v3.z);
            //TODO: here the points are still nice
            triangles.push_back(new Triangle(point1, point2, point3));
        }
        obj = ObjectPtr(new Mesh(triangles));
    }else if(node["type"] == "plane")
    {
        Point pos(node["position"]);
        Vector normal(node["normal"]);
        obj = ObjectPtr(new Plane(pos, normal));
    } else if (node["type"] == "cylinder")
    {
        Point pos(node["position"]);
        Vector direction(node["direction"]);
        double radius = node["radius"];
        //double height = node["height"];
        obj = ObjectPtr(new Cylinder(pos, direction, radius));
    }else if(node["type"] == "quad")
    {
        Point pos1(node["pos1"]);
        Point pos2(node["pos2"]);
        Point pos3(node["pos3"]);
        Point pos4(node["pos4"]);
        obj = ObjectPtr(new Quad(pos1, pos2, pos3, pos4));
    }else
    {
        cerr << "Unknown object type: " << node["type"] << ".\n";
    }

// =============================================================================
// -- End of object reading ----------------------------------------------------
// =============================================================================

    if (!obj)
        return false;

    // Parse material and add object to the scene
    obj->material = parseMaterialNode(node["material"]);
    scene.addObject(obj);
    return true;
}

Light Raytracer::parseLightNode(json const &node) const
{
    Point pos(node["position"]);
    Color col(node["color"]);
    return Light(pos, col);
}

Material Raytracer::parseMaterialNode(json const &node) const
{
    Color color(node["color"]);
    double ka = node["ka"];
    double kd = node["kd"];
    double ks = node["ks"];
    double n  = node["n"];
    return Material(color, ka, kd, ks, n);
}

bool Raytracer::readScene(string const &ifname)
try
{
    // Read and parse input json file
    ifstream infile(ifname);
    if (!infile) throw runtime_error("Could not open input file for reading.");
    json jsonscene;
    infile >> jsonscene;

// =============================================================================
// -- Read your scene data in this section -------------------------------------
// =============================================================================

    Point eye(jsonscene["Eye"]);
    scene.setEye(eye);

    // TODO: add your other configuration settings here

    for (auto const &lightNode : jsonscene["Lights"])
        scene.addLight(parseLightNode(lightNode));

    unsigned objCount = 0;
    for (auto const &objectNode : jsonscene["Objects"])
        if (parseObjectNode(objectNode))
            ++objCount;

    cout << "Parsed " << objCount << " objects.\n";

// =============================================================================
// -- End of scene data reading ------------------------------------------------
// =============================================================================

    return true;
}
catch (exception const &ex)
{
    cerr << ex.what() << '\n';
    return false;
}

void Raytracer::renderToFile(string const &ofname)
{
    // TODO: the size may be a settings in your file
    Image img(400, 400);
    cout << "Tracing...\n";
    scene.render(img);
    cout << "Writing image to " << ofname << "...\n";
    img.write_png(ofname);
    cout << "Done.\n";
}
