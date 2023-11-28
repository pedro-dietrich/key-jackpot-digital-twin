#pragma once

#include "Mesh/Mesh.hpp"

class Model
{
    public:
        // Creates a model from a .gltf file
        Model(const char* modelFile, ShaderProgram& shader);

        // Draws the whole model
        void draw(Camera& camera);

        // Sets the position and rotation of the model
        void setPosition(glm::vec3 position);
        void setRotation(float angle, glm::vec3 rotationAxis);
        void setScale(glm::vec3 scale);

    private:
        // Meshes that compose the model
        std::vector<Mesh> meshes;
        // Tranformation matrices for each mesh
        std::vector<glm::mat4> transformationMatrices;

        // Shader for the model
        ShaderProgram* shaderProgram;

        // Transformation vectors and quaternion for the model
        glm::vec3 translationVector;
        glm::quat rotationQuaternion;
        glm::vec3 scaleVector;
};
