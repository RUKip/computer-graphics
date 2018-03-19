#version 330 core

// Define constants
#define M_PI 3.141593
#define AMOUNT_OF_WAVES 4

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNormals_in;
layout (location = 2) in vec2 texCoords_in;

// Specify the Uniforms of the vertex shader
uniform mat4 modelViewTransform;
uniform mat4 projectionTransform;
uniform vec3 lightPosition;
uniform mat3 normalTransform;
uniform float amplitude[AMOUNT_OF_WAVES];
uniform float frequency[AMOUNT_OF_WAVES];
uniform float phase[AMOUNT_OF_WAVES];
uniform float time;

// Specify the output of the vertex stage
out float heightOut;
out vec3 vertNormal;
out vec3 vertPosition;
out vec3 relativeLightPosition;
out vec2 texCoords;

float waveHeight(int waveIdx, float uvalue){
    return (amplitude[waveIdx]*sin(2*M_PI*(frequency[waveIdx]*uvalue)+phase[waveIdx]+time));
}

float waveDU(int waveIdx, float uvalue){
    return (amplitude[waveIdx]*2*M_PI*frequency[waveIdx]*cos(2*M_PI*(frequency[waveIdx]*uvalue)+phase[waveIdx]+time));
}

void main()
{

    vec3 currentPosition = vertCoordinates_in;

    float height = 0;
    float derivative = 0;
    for(int i=0; i<AMOUNT_OF_WAVES; i++){
        height += waveHeight(i, texCoords_in.x);
        derivative += waveDU(i, texCoords_in.x);
    }
    vec3 normal = normalize(vec3(-derivative, 0.0, 1.0));

    heightOut = height;
    currentPosition.z = height;

    gl_Position  = projectionTransform * modelViewTransform * vec4(currentPosition, 1.0);


    // Pass the required information to the fragment stage.
    relativeLightPosition = vec3(modelViewTransform * vec4(lightPosition, 1));
    vertPosition = vec3(modelViewTransform * vec4(currentPosition, 1));
    vertNormal   = normalTransform * normal;
    texCoords    = texCoords_in;
}
