#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNormals_in;
layout (location = 2) in vec2 texCoords_in;

// Specify the Uniforms of the vertex shader
uniform mat4 modelViewTransform;
uniform mat4 projectionTransform;
uniform vec3 lightPosition;
uniform mat3 normalTransform;

// Specify the output of the vertex stage
out vec3 vertNormal;
out vec3 vertPosition;
out vec3 relativeLightPosition;
out vec2 texCoords;

void main()
{

    vec3 currentPosition = vertCoordinates_in;

    float amplitude = 0.2;
    float frequency = 10;
    float phase = 1;
    float time = 0;
    float height = amplitude*sin(2*M_PI*(frequency*texCoords_in.x)+phase+time);
    float derivative = amplitude*2*M_PI*frequency*cos(2*M_PI*(frequency*texCoords_in.x)+phase+time);

    currentPosition.z = height;

    gl_Position  = projectionTransform * modelViewTransform * vec4(currentPosition, 1.0);


    // Pass the required information to the fragment stage.
    relativeLightPosition = vec3(modelViewTransform * vec4(lightPosition, 1));
    vertPosition = vec3(modelViewTransform * vec4(currentPosition, 1));
    vertNormal   = normalTransform * vertNormals_in;
    texCoords    = texCoords_in;
}
