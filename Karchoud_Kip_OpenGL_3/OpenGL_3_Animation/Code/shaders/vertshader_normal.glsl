#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNormal_in;

// Specify the Uniforms of the vertex shader
// uniform mat4 modelTransform; for example
uniform mat4 projectionTransform_Normal;
uniform mat4 modelTransform_Normal;
uniform mat3 normalTransform_Normal;

// Specify the output of the vertex stage
out vec3 vertNormal;


void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    gl_Position = projectionTransform_Normal * modelTransform_Normal * vec4(vertCoordinates_in, 1.0);
    vertNormal = normalize(normalTransform_Normal*vertNormal_in);
}
