#include "VBO.hpp"

// VBO constructor
VBO::VBO(std::vector<Vertex>& vertices)
{
    // Generates the VBO with only 1 object
    glGenBuffers(1, &ID);
    // Binds the VBO
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    // Introduces the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

// Makes this VBO the current one
void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Makes this VBO be no longer the current one
void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes this VBO
void VBO::destroy()
{
    glDeleteBuffers(1, &ID);
}
