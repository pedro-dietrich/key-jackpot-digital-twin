#pragma once

#include <glad/glad.h>

#include "VBO.hpp"

// Vertex Array Object (VAO)
class VAO
{
    public:
        // Reference ID of the VAO
        GLuint ID;

        // VAO constructor
        VAO();

        // Links a VBO to this VAO
        void linkAttribute(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset);

        // Makes this VAO the current one
        void bind();
        // Makes this VAO be no longer the current one
        void unbind();
        // Deletes this VAO
        void destroy();
};
