#version 120

// Inputs the texture coordinates
varying vec2 texCoord;

// Gets the texture unit
uniform sampler2D diffuse;

void main()
{
    // Outputs the color using RGBA
    gl_FragColor = texture2D(diffuse, texCoord);
}
