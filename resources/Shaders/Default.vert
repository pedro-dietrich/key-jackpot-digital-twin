#version 120

// Positions
attribute vec3 aPos;
// Texture coordinates
attribute vec2 aTex;

// Inputs the transformation matrices
uniform mat4 translation;
uniform mat4 rotation;

// Outputs the texture coordinates to the fragment shader
varying vec2 texCoord;

void main()
{
    // Passes the texture coordinates to the fragment shader
    texCoord = aTex;

    // Applies the transformation matrices and output the vertices positions
    gl_Position = translation * rotation * vec4(aPos, 1.0f);
}
