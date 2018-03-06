#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec4 worldPosition;
in vec3 vertNormal;

in vec2 texCoord;

// Specify the Uniforms of the fragment shaders
// uniform vec3 lightPosition; // for example

uniform sampler2D texture;
uniform vec3 material_Color_Cell;
uniform vec4 material_Components_Cell;
uniform vec3 light_Position_Cell;
uniform vec3 light_Color_Cell;

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

void main()
{
    float edgeValue = dot(normalize(vertNormal), normalize(-worldPosition.xyz));
    if(edgeValue<0.5 && edgeValue>0){
        fColor = vec4(0.1,0.1,0.1,1); //black color
    }else{
        vec3 ambient = material_Components_Cell.x*material_Color_Cell;

        //below is for ligth not fixed TODO: add boolean uniform to set unset fixed lighting
        vec3 diffuse = vec3(0.0,0.0,0.0);
        vec3 specular = vec3(0.0,0.0,0.0);
        //below should be done over all the lights,  //TODO: what if we want to incorparate more lights?? Do we send an array of lights to the shader??
        vec3 L = normalize(light_Position_Cell - worldPosition.xyz);
        vec3 R = normalize(-reflect(L, vertNormal));
        diffuse += max(0.0, dot(L,vertNormal))*material_Color_Cell*material_Components_Cell.y*light_Color_Cell;
        specular += pow(max(0.0, dot(R, -1*worldPosition.xyz)), material_Components_Cell.w)*light_Color_Cell*material_Components_Cell.z;


        //cell shading, not fully implemented, still needs heavy lines (fat mesh)
        int numShades = 5;
        vec4 shadeIntensity = ceil(vec4(ambient+diffuse+specular,1.0)*numShades)/numShades;
        fColor = vec4(material_Color_Cell,1)*shadeIntensity*texture2D(texture, texCoord);
        fColor = vec4(material_Color_Cell,1)*shadeIntensity;
    }

}



