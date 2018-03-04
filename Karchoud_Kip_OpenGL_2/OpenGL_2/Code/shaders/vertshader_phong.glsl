#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNormal_in;
layout (location = 2) in vec2 textureCoordinates;


// Specify the Uniforms of the vertex shader
// uniform mat4 modelTransform; for example
uniform mat4 projectionTransform_Phong;
uniform mat4 modelTransform_Phong;
uniform mat3 normalTransform_Phong;

// Specify the output of the vertex stage
out vec4 worldPosition;
out vec3 vertNormal;


//incoming texture coordinates
out vec2 texCoord;

void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    // Currently without any transformation
    gl_Position = projectionTransform_Phong * modelTransform_Phong * vec4(vertCoordinates_in, 1.0);

//    //Below for non fixed lighting
    worldPosition = modelTransform_Phong*vec4(vertCoordinates_in,1);
    vertNormal = normalize(normalTransform_Phong*vertNormal_in);
    texCoord = textureCoordinates;
}
