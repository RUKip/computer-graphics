#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNormal_in;
layout (location = 2) in vec2 textureCoordinates;


// Specify the Uniforms of the vertex shader
// uniform mat4 modelTransform; for example
uniform mat4 projectionTransform_Silhouette;
uniform mat4 modelTransform_Silhouette;

void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    // Currently without any transformation
    gl_Position = projectionTransform_Silhouette * modelTransform_Silhouette * vec4(vertCoordinates_in, 1.0);
}
