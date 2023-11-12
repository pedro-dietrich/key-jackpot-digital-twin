#pragma once

#include <glad/glad.h>

#include "ShaderProgram.hpp"

class Texture
{
    public:
        // Reference ID of the texture
        GLuint ID;
        // OpenGL texture unit slot
        GLuint slot;

        // Texture constructor
        Texture(const char* imageFile, GLuint slot);

        // Assigns a texture unit to a texture
        void textureUnit(ShaderProgram &shader, const char* uniform, GLuint unit);

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
