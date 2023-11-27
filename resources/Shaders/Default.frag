#version 120

// Inputs the texture coordinates
varying vec2 texCoord;
varying vec3 normal;

// Gets the texture unit
uniform sampler2D diffuse;

void main()
{
    // Ambient lightning
    float ambientLight = 0.15f;

    // Normalizes the normal
    vec3 normalizedNormal = normalize(normal);
    // Sets the lights direction
    vec3 lightDirection0 = normalize(vec3(0.8f, 1.0f, 0.6f));
    vec3 lightDirection1 = normalize(vec3(-1.0f, 0.75f, -1.0f));
    // Calculates the light intensity on the surface
    float diffuseIntensity0 = max(0.8f * dot(normalizedNormal, lightDirection0), 0.0f);
    float diffuseIntensity1 = max(0.25f * dot(normalizedNormal, lightDirection1), 0.0f);
    float diffuseIntensity = diffuseIntensity0 + diffuseIntensity1;

    // Outputs the color using RGBA
    gl_FragColor = texture2D(diffuse, texCoord) * (ambientLight + diffuseIntensity);
}
