#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertColor_in;
layout (location = 2) in vec3 vertNormal_in;
layout (location = 3) in vec2 uvCoordinates_in;

// Specify the Uniforms of the vertex shader
 uniform mat4 modelViewTransform;
 uniform mat4 projectionTransform;
 uniform mat3 normalTransform;


// Specify the output of the vertex stage
out vec3 vertColor;
out vec3 vertNormal;
out vec3 vertPosition;
out vec2 uvCoordinates;

void main()
{
    vec3 currentPosition = vertCoordinates_in;

    float amplitude = 2;
    float frequency = 12;
    float phase = 0;
    float time = 0;
    float height = amplitude*sin(2*M_PI*((frequency∗position)+phase+time));

    // gl_Position is the output (a vec4) of the vertex shader
    // Currently without any transformation
    gl_Position     = projectionTransform * modelViewTransform * vec4(vertCoordinates_in, 1.0);
    vertColor       = vertColor_in;
    uvCoordinates   = uvCoordinates_in;
    vertPosition    = currentPosition;

}
