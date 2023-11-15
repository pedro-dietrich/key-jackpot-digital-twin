#pragma once

#include <vector>
#include <nlohmann/json.hpp>

#include "Mesh/Mesh.hpp"

class ModelLoader
{
    public:
        // Loads the model from a .gltf file
        ModelLoader
        (
            const char* modelFile,
            ShaderProgram& shader,
            std::vector<Mesh>& meshVector,
            std::vector<glm::mat4>& transformationMatrixVector
        );

    private:
        // Saves the file name, its data and the data in JSON format
        const char* file;
        std::vector<unsigned char> data;
        nlohmann::json JSON;

        // The meshes and transformation matrices of the model
        std::vector<Mesh>* meshes;
        std::vector<glm::mat4>* transformationMatrices;
        // Shader program the model will use
        ShaderProgram* shaderProgram;

        // Stores the names and textures, preventing loading the same texture more than once
        static std::vector<std::string> loadedTextureNames;
        static std::vector<Texture> loadedTextures;

        // Gets information about the JSON object
        void getJSONData();

        // Gets the transformation values from the JSON for each mesh, recursevely
        void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));
        // Loads a mesh into the mesh vector
        void loadMesh(unsigned int meshIndex);

        // Groups the position, normal and texture vectors in a Vertex vector
        std::vector<Vertex> assembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec2> textureUVs);

        // Gets specific information from the JSON
        std::vector<float> getFloats(nlohmann::json accessor);
        std::vector<GLuint> getIndices(nlohmann::json accessor);
        std::vector<Texture> getTextures();

        // Converts a float vector into a glm::vec-n (n = [2, 3, 4])
        std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVector);
        std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVector);
        std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVector);
};
