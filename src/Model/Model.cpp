#include "Model.hpp"

#include "ModelLoader.hpp"

// Creates a model from a .gltf file
Model::Model(const char* modelFile, ShaderProgram& shader)
{
    shaderProgram = &shader;

    // Initialize vectors
    meshes = std::vector<Mesh>();
    transformationMatrices = std::vector<glm::mat4>();

    // Loads the model
    ModelLoader loader(modelFile, *shaderProgram, meshes, transformationMatrices);

    // Initial values for the model modifiers
    translationVector = glm::vec3(0.0f, 0.0f, 0.0f);
    rotationQuaternion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    scaleVector = glm::vec3(1.0f, 1.0f, 1.0f);
}

// Draws the whole model
void Model::draw(Camera& camera)
{
    for(unsigned int i=0; i<meshes.size(); i++)
    {
        meshes[i].draw(camera, translationVector, rotationQuaternion, scaleVector);
    }
}

// Updates the model position
void Model::setPosition(glm::vec3 position)
{
    translationVector = position;
}

// Updates the model rotation
void Model::setRotation(float angle, glm::vec3 rotationAxis)
{
    rotationQuaternion = glm::angleAxis(glm::radians(angle), rotationAxis);
}

// Update the model scale
void Model::setScale(glm::vec3 scale)
{
    scaleVector = scale;
}
