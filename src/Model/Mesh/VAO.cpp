#include "VAO.hpp"

// VAO constructor
VAO::VAO()
{
    // Generate 1 Vertex Array instance
    glGenVertexArrays(1, &ID);
}

// Links a VBO to this VAO
void VAO::linkAttribute(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset)
{
    // Binds this VAO and the VBO which the Vertex Attributes will be set
    this->bind();
    vbo.bind();

    // Configures the Vertex Attribute, so OpenGL knows how to read the VBO
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    // Enables the Vertex Attribute
    glEnableVertexAttribArray(layout);

    // Unbinds the configured VBO, then this VAO
    vbo.unbind();
    this->unbind();
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

// Deletes this VAO
void VAO::destroy()
{
    glDeleteVertexArrays(1, &ID);
}
