#pragma once

#include <glad/glad.h>

class Texture
{
    public:
        // Reference ID of the texture
        GLuint ID;

        // Texture constructor
        Texture(const char* imageFile);

        // Makes this texture the current one
        void bind();
        // Makes this texture be no longer the current one
        void unbind();
        // Deletes this texture
        void destroy();

    private:
        // Texture's image format according to the number of color channels
        unsigned int imageFormat;

        // Sets the texture parameters
        void setImageParameters(int numberColorChannels);
};
