#include "Mesh.hpp"

#include "VBO.hpp"
#include "EBO.hpp"

// Creates a mesh
Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices)
{
    this->vertices = vertices;
    this->indices = indices;

    generateMeshObjects();
}

// Generates the VBO and the EBO, linking them to the VAO
void Mesh::generateMeshObjects()
{
    // Creates the VBO and EBO
    VBO vbo(vertices);
    EBO ebo(indices);

    // Links VBO attributes (vertex and texture coordinates) to the VAO
    vao.linkAttribute(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) 0);
    vao.linkAttribute(vbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*) (2*sizeof(float)));
}
