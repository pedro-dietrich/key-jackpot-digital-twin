#include "Texture.hpp"

#include <iostream>
#include <stb_image.h>

// Texture constructor
Texture::Texture(const char* imageFile)
{
    // Loads the texture image and its parameters
    int width, height, numberColorChannels;
    unsigned char* imageBytes = stbi_load(imageFile, &width, &height, &numberColorChannels, 0);

    // Generates an OpenGL texture object
    glGenTextures(1, &ID);
    // Assigns the texture to a Texture Unit
    bind();

    // Configures the texture parameters
    setImageParameters(numberColorChannels);

    // Assigns the image to the OpenGL Texture Object
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, imageBytes);

    // Deletes the image data (already used)
    stbi_image_free(imageBytes);
    // Unbinds the texture to prevent unintentional modifications
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Makes this texture the current one
void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);
}

// Makes this texture be no longer the current one
void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Deletes this texture
void Texture::destroy()
{
    glDeleteTextures(1, &ID);
}

// Sets the texture parameters
void Texture::setImageParameters(int numberColorChannels)
{
    // Sets the texture parameters for rendering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Sets the image format
    switch(numberColorChannels)
    {
        case 4:
            this->imageFormat = GL_RGBA;  // 4 color channels -> RGBA
            break;

        case 3:
            this->imageFormat = GL_RGB;   // 3 color channels -> RGB
            break;

        case 1:
            this->imageFormat = GL_RED;   // 1 color channel -> Black and white
            break;

        default:
            throw std::invalid_argument("Automatic texture type recognition failed.");
    }

    // Generates MipMaps
    glGenerateMipmap(GL_TEXTURE_2D);
}