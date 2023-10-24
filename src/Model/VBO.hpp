#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

// Stores the position and the texture coordinate of a vertex
struct Vertex
{
    glm::vec3 position;
    glm::vec2 textureUV;
};

// Vertex Array Buffer Object (VBO)
class VBO
{
    public:
        //Reference ID of the VBO
        GLuint ID;

        // VBO constructor
        VBO(std::vector<Vertex>& vertices);

        // Makes this VBO the current one
        void bind();
        // Makes this VBO be no longer the current one
        void unbind();
        // Deletes this VBO
        void destroy();
};
