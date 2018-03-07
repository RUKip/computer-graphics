 #include "scene.h"

#include "hit.h"
#include "image.h"
#include "material.h"
#include "ray.h"

#include <cmath>
#include <limits>
#include <iostream>

using namespace std;

Color Scene::trace(Ray const &ray, int reflectionDepth)
{
    // Find hit object and distance
    Hit min_hit(numeric_limits<double>::infinity(), Vector());
    ObjectPtr obj = nullptr;
    for (unsigned idx = 0; idx != objects.size(); ++idx)
    {
        Hit hit(objects[idx]->intersect(ray));
        if (hit.t < min_hit.t)
        {
            min_hit = hit;
            obj = objects[idx];
        }
    }

    // No hit? Return background color.
    if (!obj) return Color(0.0, 0.0, 0.0);

    Material material = obj->material;          //the hit objects material
    Point hit = ray.at(min_hit.t);                 //the hit point
    Vector N = min_hit.N;                          //the normal at hit point
    Vector V = -ray.D;                             //the view vector

    if(obj->hasTex){
        Vector uv = obj->getTextureCoordinates(hit);
        material.color = obj->texture.colorAt(uv.x, uv.y);
    }

    /****************************************************
    * This is where you should insert the color
    * calculation (Phong model).
    *
    * Given: material, hit, N, V, lights[]
    * Sought: color
    *
    * Hints: (see triple.h)
    *        Triple.dot(Vector) dot product
    *        Vector + Vector    vector sum
    *        Vector - Vector    vector difference
    *        Point - Point      yields vector
    *        Vector.normalize() normalizes vector, returns length
    *        double * Color     scales each color component (r,g,b)
    *        Color * Color      dito
    *        pow(a,b)           a to the power of b
    ****************************************************/
    const float CONSTANT_MOVEMENT_DIR = 0.1;

    Color intensityA = material.color * material.ka;
    Color intensityD = Color(0.0,0.0,0.0);
    Color intensityS = Color(0.0,0.0,0.0);
    Color reflectedColor = Color(0.0,0.0,0.0);

    //Reflection stuff
    if(reflectionDepth<maxRecursionDepth){ //should be maximum amount of reflections
        Vector R = (2*(N.dot(V))*N - V).normalized();
        Ray reflectionRay = Ray(hit+(R*CONSTANT_MOVEMENT_DIR), R);
        reflectedColor = trace(reflectionRay, reflectionDepth+1)*material.ks;
    }

    for(unsigned int i=0; i<lights.size(); i++){
         //material diffuse part
        Light light = *lights[i];
        Vector L = (light.position - hit).normalized();

        //Shadow stuff
        if(shadows){
            Vector shadowDir = (light.position - hit).normalized();
            Ray shadowRay = Ray(hit+(shadowDir*CONSTANT_MOVEMENT_DIR),shadowDir);
            Hit min_hit(numeric_limits<double>::infinity(), Vector());
            ObjectPtr obj = nullptr;
            bool hasHit = false;
            for (unsigned idx = 0; idx != objects.size(); ++idx)
            {
                Hit hitS(objects[idx]->intersect(shadowRay));
                if (hitS.t < min_hit.t)
                {
                    hasHit=true;
                    break;
                }
            }
            if(hasHit) continue;
        }

        intensityD +=  light.color * max(0.0,(L.dot(N))) * material.color * material.kd;

        //material specular part
        Vector R = -1*(L - 2*(L.dot(N))*N).normalized();
        intensityS += light.color * pow(max(0.0, R.dot(V)), material.n) * material.ks;
    }

    Color color = intensityA + intensityD + intensityS;

    return color+reflectedColor;
}

void Scene::render(Image &img)
{
    unsigned w = img.width();
    unsigned h = img.height();
    #pragma omp parallel for
    for (unsigned y = 0; y < h; ++y)
    {
        for (unsigned x = 0; x < w; ++x)
        {
            Color col = Color(0.0,0.0,0.0);
            for(int i=0; i<superSampling; i++){
                double xOffset = (i+1)*((double)1/(superSampling+1));
                for(int j=0; j<superSampling; j++){
                    double yOffset = (j+1)*((double)1/(superSampling+1));
                    Point pixel(x + xOffset, h - 1 - y + yOffset, 0);
                    Ray ray(eye, (pixel - eye).normalized());
                    col += trace(ray, 0);
                }
            }
            col = col/((double) superSampling*superSampling);
            col.clamp();
            img(x, y) = col;
        }
    }
}

// --- Misc functions ----------------------------------------------------------

void Scene::addObject(ObjectPtr obj)
{
    objects.push_back(obj);
}

void Scene::addLight(Light const &light)
{
    lights.push_back(LightPtr(new Light(light)));
}

void Scene::setEye(Triple const &position)
{
    eye = position;
}

void Scene::setShadows(bool value){
    shadows = value;
}

void Scene::setMaxRecursionDepth(int depth){
    maxRecursionDepth = depth;
}

void Scene::setSuperSampling(int value){
    superSampling = value;
}

unsigned Scene::getNumObject()
{
    return objects.size();
}

unsigned Scene::getNumLights()
{
    return lights.size();
}
