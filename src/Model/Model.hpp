#pragma once

#include "Mesh/Mesh.hpp"

class Model
{
    public:
        // Creates a model from a .gltf file
        Model(const char* modelFile, ShaderProgram& shader);

        // Draws the whole model
        void draw();

        // Sets the position and rotation of the model
        void setPosition(glm::vec3 position);
        void setRotation(float angle, glm::vec3 rotationAxis);

    private:
        // Meshes that compose the model
        std::vector<Mesh> meshes;
        // Tranformation matrices for each mesh
        std::vector<glm::mat4> transformationMatrices;

        // Shader for the model
        ShaderProgram* shaderProgram;

        // Transformation vector and quaternion for the model
        glm::vec3 translationVector;
        glm::quat rotationQuaternion;
};
