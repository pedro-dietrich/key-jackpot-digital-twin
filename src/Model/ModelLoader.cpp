#include "ModelLoader.hpp"

#include <string>
#include <glm/gtc/type_ptr.hpp>

#include "../Helpers/FileHandler.hpp"

// Initialize static members
std::vector<std::string> ModelLoader::loadedTextureNames;
std::vector<Texture> ModelLoader::loadedTextures;

// Loads the model from a .gltf file
ModelLoader::ModelLoader
(
    const char* modelFile,
    ShaderProgram& shader,
    std::vector<Mesh>& meshVector,
    std::vector<glm::mat4>& transformationMatrixVector
)
{
    file = modelFile;
    std::string text = FileHandler::getFileContents("resources/Models/", file);
    JSON = nlohmann::json::parse(text);

    shaderProgram = &shader;

    meshes = &meshVector;
    transformationMatrices = &transformationMatrixVector;

    getJSONData();

    traverseNode(0);
}

// Gets specific informations from the JSON object
void ModelLoader::getJSONData()
{
    // Gets the URI from the JSON
    std::string uri = JSON["buffers"][0]["uri"];

    // Puts the file's content into a string
    std::string fileStr = std::string(file);
    std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
    std::string bytesText = FileHandler::getFileContents("resources/Models/", (fileDirectory + uri).c_str());

    // Puts the file's content into a char vector
    data = std::vector<unsigned char>(bytesText.begin(), bytesText.end());
}

// Gets the transformation values from the JSON for each mesh, recursevely
void ModelLoader::traverseNode(unsigned int nextNode, glm::mat4 matrix)
{
    // Creates a new JSON for the node
    nlohmann::json node = JSON["nodes"][nextNode];
    // Copies the transformation values into their respective vectors
    glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
    if(node.find("translation") != node.end())
    {
        float translationValues[3];
        for(int i=0; i<node["translation"].size(); i++)
        {
            translationValues[i] = (node["translation"][i]);
        }
        translation = glm::make_vec3(translationValues);
    }
    glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    if(node.find("rotation") != node.end())
    {
        float rotationValues[4] =
        {
            node["rotation"][3],
            node["rotation"][0],
            node["rotation"][1],
            node["rotation"][2]
        };
        rotation = glm::make_quat(rotationValues);
    }
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    if(node.find("scale") != node.end())
    {
        float scaleValues[3];
        for(int i=0; i<node["scale"].size(); i++)
        {
            scaleValues[i] = (node["scale"][i]);
        }
        scale = glm::make_vec3(scaleValues);
    }
    glm::mat4 matrixNode = glm::mat4(1.0f);
    if(node.find("matrix") != node.end())
    {
        float matrixValues[16];
        for(int i=0; i<node["matrix"].size(); i++)
        {
            matrixValues[i] = (node["matrix"][i]);
        }
        matrixNode = glm::make_mat4(matrixValues);
    }

    // Initializes the transformation matrices
    glm::mat4 translationMatrix = glm::mat4(1.0f);
    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    glm::mat4 scaleMatrix = glm::mat4(1.0f);
    // Configures the transformation matrices
    translationMatrix = glm::translate(translationMatrix, translation);
    rotationMatrix = glm::mat4_cast(rotation);
    scaleMatrix = glm::scale(scaleMatrix, scale);
    // Gets the final transformation matrix
    glm::mat4 nextNodeMatrix = matrix * matrixNode * translationMatrix * rotationMatrix * scaleMatrix;

    // Assign the matrices to their respective vectors and loads the associated mesh
    if(node.find("mesh") != node.end())
    {
        transformationMatrices->push_back(nextNodeMatrix);

        loadMesh(node["mesh"]);
    }

    // Use recursion to apply the same traverse treatment to the children nodes
    if(node.find("children") != node.end())
    {
        for(unsigned int i=0; i<node["children"].size(); i++)
        {
            traverseNode(node["children"][i], nextNodeMatrix);
        }
    }
}

// Loads a mesh into the mesh vector
void ModelLoader::loadMesh(unsigned int meshIndex)
{
    // Gets the indices of all the vertices accessors
    unsigned int posAccIndex = JSON["meshes"][meshIndex]["primitives"][0]["attributes"]["POSITION"];
    unsigned int texAccIndex = JSON["meshes"][meshIndex]["primitives"][0]["attributes"]["TEXCOORD_0"];
    unsigned int indAccIndex = JSON["meshes"][meshIndex]["primitives"][0]["indices"];

    // Gets the position and texture coordinates vectors
    std::vector<float> posVec = getFloats(JSON["accessors"][posAccIndex]);
    std::vector<glm::vec3> positions = groupFloatsVec3(posVec);
    std::vector<float> texVec = getFloats(JSON["accessors"][texAccIndex]);
    std::vector<glm::vec2> textureUVs = groupFloatsVec2(texVec);

    // Assembles the vertices and gets the indices and textures
    std::vector<Vertex> vertices = assembleVertices(positions, textureUVs);
    std::vector<GLuint> indices = getIndices(JSON["accessors"][indAccIndex]);
    std::vector<Texture> textures = getTextures();

    // Pushes the mesh into the mesh vector
    meshes->push_back(Mesh(vertices, indices, textures, *shaderProgram));
}

// Groups the position, normal and texture vectors in a Vertex vector
std::vector<Vertex> ModelLoader::assembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec2> textureUVs)
{
    std::vector<Vertex> vertices;
    for(unsigned int i=0; i<positions.size(); i++)
    {
        vertices.push_back(Vertex{positions[i], textureUVs[i]});
    }

    return vertices;
}

// Gets floats from the JSON
std::vector<float> ModelLoader::getFloats(nlohmann::json accessor)
{
    // Initializes the float vector
    std::vector<float> floatVector;

    // Gets the buffer view, the count, the offset and the type from the JSON
    unsigned int bufferViewIndex = accessor.value("bufferView", 1);
    unsigned int count = accessor["count"];
    unsigned int accByteOffset = accessor.value("byteOffset", 0);
    std::string type = accessor["type"];

    // Creates a JSON with only the buffer views and copies the data bytes into a float vector
    nlohmann::json bufferView = JSON["bufferViews"][bufferViewIndex];
    unsigned int byteOffset = bufferView["byteOffset"];

    // Stores the type size
    unsigned int numPerVert;
    if(type == "SCALAR")
        numPerVert = 1;
    else if(type == "VEC2")
        numPerVert = 2;
    else if(type == "VEC3")
        numPerVert = 3;
    else if(type == "VEC4")
        numPerVert = 4;
    else
        throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3 or VEC4).");

    // Calculates the beggining and length of the data, and copies the data bytes into a float vector
    unsigned int begginingOfData = byteOffset + accByteOffset;
    unsigned int lengthOfData = count * 4 * numPerVert;
    for(unsigned int i=begginingOfData; i<begginingOfData + lengthOfData; i)
    {
        unsigned char bytes[] = {data[i++], data[i++], data[i++], data[i++]};
        float value;
        std::memcpy(&value, bytes, sizeof(float));
        floatVector.push_back(value);
    }

    return floatVector;
}

// Get indices from the JSON
std::vector<GLuint> ModelLoader::getIndices(nlohmann::json accessor)
{
    // Initializes the indices vector
    std::vector<GLuint> indices;

    // Gets the buffer view, the count, the offset and the type from the JSON
    unsigned int bufferViewIndex = accessor.value("bufferView", 0);
    unsigned int count = accessor["count"];
    unsigned int accByteOffset = accessor.value("byteOffset", 0);
    unsigned int componentType = accessor["componentType"];

    // Creates a JSON with only the buffer views and gets its offset
    nlohmann::json bufferView = JSON["bufferViews"][bufferViewIndex];
    unsigned int byteOffset = bufferView["byteOffset"];

    // Calculates the beggining and end of the data, copying the data bytes into a GLuint vector
    unsigned int begginingOfData = byteOffset + accByteOffset;
    unsigned int endOfData;
    switch(componentType)
    {
        // Unsigned int
        case 5125:
            endOfData = byteOffset + accByteOffset + 4 * count;
            for(unsigned int i = begginingOfData; i < endOfData; i)
            {
                unsigned char bytes[] = {data[i++], data[i++], data[i++], data[i++]};
                unsigned int value;
                std::memcpy(&value, bytes, sizeof(unsigned int));
                indices.push_back((GLuint) value);
            }
            break;

        // Unsigned short
        case 5123:
            endOfData = byteOffset + accByteOffset + 2 * count;
            for(unsigned int i = begginingOfData; i < endOfData; i)
            {
                unsigned char bytes[] = {data[i++], data[i++]};
                unsigned short value;
                std::memcpy(&value, bytes, sizeof(unsigned short));
                indices.push_back((GLuint) value);
            }
            break;

        // Short
        case 5122:
            endOfData = byteOffset + accByteOffset + 2 * count;
            for(unsigned int i = begginingOfData; i < endOfData; i)
            {
                unsigned char bytes[] = {data[i++], data[i++]};
                short value;
                std::memcpy(&value, bytes, sizeof(short));
                indices.push_back((GLuint) value);
            }
            break;

        default:
            throw std::invalid_argument("Invalid index componentType: " + componentType);
    }

    return indices;
}

// Get textures from the JSON
std::vector<Texture> ModelLoader::getTextures()
{
    // Initializes the texture vector
    std::vector<Texture> textures;

    // Gets the file's directory
    std::string fileStr = std::string(file);
    std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);

    // Saves the textures in the texture vector
    for(unsigned int i=0; i<JSON["images"].size(); i++)
    {
        std::string texPath = JSON["images"][i]["uri"];

        // Verifies if the texture has already been loaded
        bool skip = false;
        for(unsigned int j=0; j<loadedTextureNames.size(); j++)
        {
            if(loadedTextureNames[j] == texPath)
            {
                textures.push_back(loadedTextures[j]);
                skip = true;
                break;
            }
        }

        // If texture hasn't been loaded, it is stored in the texture vector
        if(!skip)
        {
            Texture diffuse = Texture((fileDirectory + texPath).c_str(), textures.size());
            textures.push_back(diffuse);
            loadedTextureNames.push_back(texPath);
            loadedTextures.push_back(diffuse);
        }
    }

    return textures;
}

// Converts a float vector into a vector of glm::vec2
std::vector<glm::vec2> ModelLoader::groupFloatsVec2(std::vector<float> floatVector)
{
    std::vector<glm::vec2> vectors;
    for(int i=0; i<floatVector.size(); i)
    {
        vectors.push_back(glm::vec2(floatVector[i++], floatVector[i++]));
    }

    return vectors;
}

// Converts a float vector into a vector of glm::vec3
std::vector<glm::vec3> ModelLoader::groupFloatsVec3(std::vector<float> floatVector)
{
    std::vector<glm::vec3> vectors;
    for(int i=0; i<floatVector.size(); i)
    {
        vectors.push_back(glm::vec3(floatVector[i++], floatVector[i++], floatVector[i++]));
    }

    return vectors;
}

// Converts a float vector into a vector of glm::vec4
std::vector<glm::vec4> ModelLoader::groupFloatsVec4(std::vector<float> floatVector)
{
    std::vector<glm::vec4> vectors;
    for(int i=0; i<floatVector.size(); i)
    {
        vectors.push_back(glm::vec4(floatVector[i++], floatVector[i++], floatVector[i++], floatVector[i++]));
    }

    return vectors;
}
