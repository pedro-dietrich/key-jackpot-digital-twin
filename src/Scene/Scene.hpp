#pragma once

#include "../Model/Model.hpp"

class Scene
{
    public:
        // Builds the scene
        Scene(Camera& cam);

        // Draws all the models in the scene
        void drawScene();
        // Deallocates memory
        void destroy();

    private:
        // Default shader program for the models
        ShaderProgram* defaultShader;
        // Camera for the scene
        Camera* camera;

        // Models of the scene
        std::vector<Model> models;

        // Creates a model
        Model createModel(const char* modelName);
};
