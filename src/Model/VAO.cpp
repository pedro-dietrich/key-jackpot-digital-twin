#include "VAO.hpp"

// VAO constructor
VAO::VAO()
{
    // Generate 1 Vertex Array instance
    glGenVertexArrays(1, &ID);
}

// Makes this VAO the current one
void VAO::bind()
{
    glBindVertexArray(ID);
}

// Makes this VAO be no longer the current one
void VAO::unbind()
{
    glBindVertexArray(0);
}

// Deletes the VAO
void VAO::destroy()
{
    glDeleteVertexArrays(1, &ID);
}
