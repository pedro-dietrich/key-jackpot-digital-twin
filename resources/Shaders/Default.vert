#version 120

// Positions
attribute vec3 aPos;
// Texture coordinates
attribute vec2 aTex;
// Normal vectors
attribute vec3 aNormal;

// Inputs the transformation matrices
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
// Camera matrix transformation for perspective
uniform mat4 camera;

// Outputs the texture coordinates and normal vectors to the fragment shader
varying vec2 texCoord;
varying vec3 normal;

void main()
{
    // Passes the normal and texture coordinates to the fragment shader
    texCoord = aTex;
    vec4 rotatedNormal = rotation * vec4(aNormal, 1.0f);
    normal = vec3(rotatedNormal.x, rotatedNormal.y, rotatedNormal.z);

    // Applies the transformation matrices
    vec4 currentPosition = translation * rotation * scale * vec4(aPos, 1.0f);
    // Applies perspective and outputs the final vertex position
    gl_Position = camera * currentPosition;
}
