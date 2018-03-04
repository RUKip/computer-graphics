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
uniform mat4 projectionTransform_Gouraud;
uniform mat4 modelTransform_Gouraud;
uniform mat3 normalTransform_Gouraud;
uniform vec3 material_Color_Gouraud;
uniform vec4 material_Components_Gouraud;
uniform vec3 light_Position_Gouraud;
uniform vec3 light_Color_Gouraud;


// Specify the output of the vertex stage
out vec4 color;

out vec2 texCoord;


void main()
{
    //We first calculate ligthing values on the original model here because of fixed lighting, TODO: this doesnt seem to work
//    vec3 diffuse = vec3(0.0,0.0,0.0);
//    vec3 specular = vec3(0.0,0.0,0.0);
//    //below should be done over all the lights,  //TODO: what if we want to incorparate more lights?? Do we send an array of lights to the shader??
//    vec3 L = normalize(light_Position_Gouraud - vertCoordinates_in);
//    vec3 R = normalize(-reflect(L, vertNormal_in));
//    diffuse += max(0.0, dot(L,vertNormal_in))*material_Color_Gouraud*material_Components_Gouraud.y*light_Color_Gouraud;
//    specular += pow(max(0.0, dot(R, -1*vertCoordinates_in)), material_Components_Gouraud.w)*light_Color_Gouraud*material_Components_Gouraud.z;


    vec4 worldPosition = modelTransform_Gouraud * vec4(vertCoordinates_in, 1.0);
    gl_Position = projectionTransform_Gouraud * worldPosition;
    vec3 vertNormal = normalize(normalTransform_Gouraud*vertNormal_in);
    vec3 ambient = material_Components_Gouraud.x*material_Color_Gouraud;

    //below is for ligth not fixed TODO: add boolean uniform to set unset fixed lighting
    vec3 diffuse = vec3(0.0,0.0,0.0);
    vec3 specular = vec3(0.0,0.0,0.0);
    //below should be done over all the lights,  //TODO: what if we want to incorparate more lights?? Do we send an array of lights to the shader??
    vec3 L = normalize(light_Position_Gouraud - worldPosition.xyz);
    vec3 R = normalize(-reflect(L, vertNormal));
    diffuse += max(0.0, dot(L,vertNormal))*material_Color_Gouraud*material_Components_Gouraud.y*light_Color_Gouraud;
    specular += pow(max(0.0, dot(R, -1*worldPosition.xyz)), material_Components_Gouraud.w)*light_Color_Gouraud*material_Components_Gouraud.z;

    color = vec4(ambient+diffuse+specular,1.0);

//    //cell shading, not fully implemented, still needs heavy lines (fat mesh)
//    int numShades = 5;
//    vec4 shadeIntensity = ceil(vec4(ambient+diffuse+specular,1.0)*numShades)/numShades;
//    color = vec4(material_Color_Gouraud,1)*shadeIntensity;

    //texture mapping
    texCoord = textureCoordinates;
}
