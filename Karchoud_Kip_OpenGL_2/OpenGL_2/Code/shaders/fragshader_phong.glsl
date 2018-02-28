#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec4 worldPosition;
in vec3 vertNormal;

// Specify the Uniforms of the fragment shaders
// uniform vec3 lightPosition; // for example
uniform vec3 material_Phong;
uniform vec3 positionLight_Phong;
uniform vec3 colorLight_Phong;

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

void main()
{
    vertNormal = normalize(vertNormal);
    vec3 ambient = material_Components_Gouraud.x*material_Color_Gouraud;
    vec3 diffuse = vec3(0.0,0.0,0.0);
    vec3 specular = vec3(0.0,0.0,0.0);
    //below should be done over all the lights,  //TODO: what if we want to incorparate more lights?? Do we send an array of lights to the shader??
    vec3 L = normalize(light_Position_Gouraud - worldPosition.xyz);
    vec3 R = normalize(-reflect(L, vertNormal));
    diffuse += max(0.0, dot(L,vertNormal))*material_Color_Gouraud*material_Components_Gouraud.y*light_Color_Gouraud;
    specular += pow(max(0.0, dot(R, normalize(worldPosition.xyz))), material_Components_Gouraud.w)*light_Color_Gouraud*material_Components_Gouraud.z;

    fNormal = vec4(ambient+diffuse+specular, 1.0);

}
