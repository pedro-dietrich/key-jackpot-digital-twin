#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "VAO.hpp"
#include "Texture.hpp"

class Mesh
{
    public:
        // Creates a mesh
        Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures, ShaderProgram& shader);

        // Draws the mesh on the screen
        void draw
        (
            glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
            glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
        );

        // Deletes the mesh
        void destroy();

    private:
        // Mesh vertices
        std::vector<Vertex> vertices;
        // Mesh indices
        std::vector<GLuint> indices;
        // Mesh textures
        std::vector<Texture> textures;
        // Mesh shader
        ShaderProgram* shaderProgram;
        // Mesh VAO
        VAO vao;

        // Generates the VBO and the EBO, linking them to the VAO
        void generateMeshObjects();
};
