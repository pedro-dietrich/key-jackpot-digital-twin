#include "EBO.hpp"

// EBO constructor
EBO::EBO(std::vector<GLuint>& indices)
{
    // Generates 1 Element Array Buffer instance
    glGenBuffers(1, &ID);
    // Binds, links the EBO and then unbinds it
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Makes this EBO the current one
void EBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Makes this EBO be no longer the current one
void EBO::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes this EBO
void EBO::destroy()
{
    glDeleteBuffers(1, &ID);
}
