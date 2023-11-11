#pragma once

#include <vector>

#include <glad/glad.h>

// Element Array Buffer Object (EBO)
class EBO
{
    public:
        // Reference ID of the EBO
        GLuint ID;

        // EBO constructor
        EBO(std::vector<GLuint>& indices);

        // Makes this EBO the current one
        void bind();
        // Makes this EBO be no longer the current one
        void unbind();
        // Deletes this EBO
        void destroy();
};
