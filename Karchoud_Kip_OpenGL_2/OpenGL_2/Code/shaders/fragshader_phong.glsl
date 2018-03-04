#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec4 worldPosition;
in vec3 vertNormal;

//texture coordinates
in vec2 texCoord;

// Specify the Uniforms of the fragment shaders
// uniform vec3 lightPosition; // for example
uniform vec3 material_Color_Phong;
uniform vec4 material_Components_Phong;
uniform vec3 light_Position_Phong;
uniform vec3 light_Color_Phong;

uniform sampler2D texture;

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

void main()
{
    vec3 normal = normalize(vertNormal);
    vec3 ambient = (material_Components_Phong.x)*material_Color_Phong;
    vec3 diffuse = vec3(0.0,0.0,0.0);
    vec3 specular = vec3(0.0,0.0,0.0);
    //below should be done over all the lights,  //TODO: what if we want to incorparate more lights?? Do we send an array of lights to the shader??
    vec3 L = normalize(light_Position_Phong - worldPosition.xyz);
    vec3 R = normalize(-reflect(L, normal));
    diffuse += max(0.0, dot(L,normal))*material_Color_Phong*material_Components_Phong.y*light_Color_Phong;
    specular += pow(max(0.0, dot(R, -1*worldPosition.xyz)), material_Components_Phong.w)*light_Color_Phong*material_Components_Phong.z;

    fColor = texture2D(texture, texCoord) * vec4(ambient+diffuse+specular, 1.0);
}
