#version 330 core

// Define constants
#define M_PI 3.141593

// The input from the vertex shader.
in float heightOut;
in vec3 vertNormal;
in vec3 vertPosition;
in vec3 relativeLightPosition;
in vec2 texCoords;

// Lighting model constants.
uniform vec4 material;
uniform vec3 lightColour;

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 vertColour;

void main()
{ 

  // Ambient colour does not depend on any vectors.
    vec3 colorWhite = vec3(1.0,1.0,1.0);
    vec3 colorBlue = vec3(0.0, 0.0,(249.0/255.0));

    float smoothValue = smoothstep(-0.3,0.1,heightOut); //Probably needs other maxvalues instead of 0 and 1
    vec3 mixedColor = mix(colorWhite, colorBlue, vec3(smoothValue, smoothValue, smoothValue));// vec3(0,0,smoothValue));
    vec3 texColour = mixedColor;

  //vec3 texColour = materialColour;
  vec3 colour    = material.x * texColour;

  // Calculate light direction vectors in the phong model.
  vec3 lightDirection   = normalize(relativeLightPosition - vertPosition);
  vec3 normal           = normalize(vertNormal);

  // Diffuse colour.
  float diffuseIntesity = max(dot(normal, lightDirection), 0);
  colour += texColour * material.y * diffuseIntesity;

  // Specular colour.
  vec3 viewDirection     = normalize(-vertPosition); // The camera is always at (0, 0, 0).
  vec3 reflectDirection  = reflect(-lightDirection, normal);
  float specularIntesity = max(dot(reflectDirection, viewDirection), 0);
  colour += texColour * lightColour * material.z * pow(specularIntesity, material.w);

  vertColour = vec4(colour, 1);
}
