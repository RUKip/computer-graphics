#ifndef OBJECT_H_
#define OBJECT_H_

#include "material.h"
#include "image.h"

// not really needed here, but deriving classes may need them
#include "hit.h"
#include "ray.h"
#include "triple.h"

#include <memory>
class Object;
typedef std::shared_ptr<Object> ObjectPtr;

class Object
{
    public:
        Material material;
        Image texture;
        bool hasTex;
        float rotationAngle;
        Vector rotationAxis;

        virtual ~Object() = default;

        virtual Vector getTextureCoordinates(Point p){
            return Vector(0);
        };
        virtual Hit intersect(Ray const &ray) = 0;  // must be implemented
                                                    // in derived class
};

#endif
