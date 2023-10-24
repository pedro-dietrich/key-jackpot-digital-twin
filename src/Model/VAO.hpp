#pragma once

#include <glad/glad.h>

// Vertex Array Object (VAO)
class VAO
{
    public:
        // Reference ID of the VAO
        GLuint ID;

        // VAO constructor
        VAO();

        // Makes this VAO the current one
        void bind();
        // Makes this VAO be no longer the current one
        void unbind();
        // Deletes the VAO
        void destroy();
};
