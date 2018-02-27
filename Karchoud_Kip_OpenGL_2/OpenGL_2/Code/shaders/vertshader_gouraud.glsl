#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNormal_in;


// Specify the Uniforms of the vertex shader
// uniform mat4 modelTransform; for example
uniform mat4 projectionTransform_Gouraud;
uniform mat4 modelTransform_Gouraud;
uniform mat3 normalTransform_Gouraud;
uniform vec3 material_Gouraud;
uniform vec3 positionLight_Gouraud;
uniform vec3 colorLight_Gouraud;


// Specify the output of the vertex stage
out vec4 color;


void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    gl_Position = projectionTransform_Gouraud * modelTransform_Gouraud * vec4(vertCoordinates_in, 1.0);
    vec3 vertNormal = normalTransform_Gouraud*vertNormal_in;
    vec3 ambient = material_ambient_Gouraud*material_color_Gouraud;

    vec3 diffuse = vec3(0.0,0.0,0.0);
    vec3 specular = vec3(0.0,0.0,0.0);
    //below should be done over all the lights,  //TODO: what if we want to incorparate more lights?? Do we send an array of lights to the shader??
    double iDiffuse = max(0.0, dot(vertNormal, normalize((positionLight_Gouraud - vertCoordinates_in))));
    double iSpecular = pow(max(0.0, dot(normalize(-reflect(L, normalize(vertNormal))), V)), specularMaterial); //TODO: what is our view V?
    diffuse += material_diffuse_Gouraud*iDiffuse*material_color;
    specular += material_specular_Gourad*iSpecular;

    color = vec4(ambient+diffuse+specular,1.0);
}
