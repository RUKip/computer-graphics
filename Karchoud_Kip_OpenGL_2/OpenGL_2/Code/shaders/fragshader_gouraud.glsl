#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec4 color;
in vec2 UV;

// Specify the Uniforms of the fragment shaders
// uniform vec3 lightPosition; // for example

uniform sampler2D texture;


// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

out vec4 textureColor;

void main()
{
    fColor = color;

    //Texture
    textureColor = texture2D(texture, UV);
}



