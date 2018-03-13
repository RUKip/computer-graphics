#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNormal_in;
layout (location = 2) in vec2 textureCoordinates;

//TODO: change material to input, input is per object

// Specify the Uniforms of the vertex shader
// uniform mat4 modelTransform; for example
uniform mat4 projectionTransform_Cell;
uniform mat4 modelTransform_Cell;
uniform mat3 normalTransform_Cell;

// Specify the output of the vertex stage
out vec4 worldPosition;
out vec3 vertNormal;
out vec2 texCoord;


void main()
{
    worldPosition = modelTransform_Cell * vec4(vertCoordinates_in, 1.0);
    gl_Position = projectionTransform_Cell * worldPosition;
    vertNormal = normalize(normalTransform_Cell*vertNormal_in);
    //texture mapping
    texCoord = textureCoordinates;
}
