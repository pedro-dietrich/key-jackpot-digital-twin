#pragma once

#include <vector>

#include "VAO.hpp"

class Mesh
{
    public:
        // Creates a mesh
        Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);

    private:
        // Mesh vertices
        std::vector<Vertex> vertices;
        // Mesh indices
        std::vector<GLuint> indices;
        // Mesh VAO
        VAO vao;

        // Generates the VBO and the EBO, linking them to the VAO
        void generateMeshObjects();
};
