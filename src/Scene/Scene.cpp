#include "Scene.hpp"

#include <iostream>
#include <string>

enum SceneModels
{
    BASE,
    AXIS_SUPPORT_0,
    AXIS_SUPPORT_1,
    AXIS_SUPPORT_2,
    AXIS_SUPPORT_3,
    AXIS_0,
    AXIS_1,
    LINEAR_BEARING_0,
    LINEAR_BEARING_1,
    LINEAR_BEARING_2,
    STEPPER_MOTOR_0,
    PLATFORM_0,
    PLATFORM_1,
    SERVOMOTOR,
    RACK,
    ULTRASSONIC_SENSOR,
    BARRIER
};

// Builds the scene
Scene::Scene(Camera& cam)
{
    // Creates the default shader program
	defaultShader = new ShaderProgram("Default.vert", "Default.frag");
    // Gets the camera object
    camera = &cam;

    // Creates the models used in the scene

    // Wooden base
    models.push_back(createModel("Base"));
    // Four axis supports
    for(int i=0; i<4; i++)
        models.push_back(createModel("AxisSupport"));
    // Two axis
    models.push_back(createModel("Axis"));
    models.push_back(createModel("Axis"));
    // Three linear bearings
    for(int i=0; i<3; i++)
        models.push_back(createModel("LinearBearing"));
    // Stepper motor
    models.push_back(createModel("StepperMotor0"));
    // Two Platforms
    models.push_back(createModel("Platform0"));
    models.push_back(createModel("Platform1"));
    // Servomotor
    models.push_back(createModel("Servomotor"));
    // Rack
    models.push_back(createModel("Rack"));
    // Ultrassonic sensor (HC-SR04)
    models.push_back(createModel("UltrassonicSensor"));
    // Barrier
    models.push_back(createModel("Barrier"));

    // Sets the models initial positions
    models[AXIS_SUPPORT_0].setPosition(glm::vec3(-70.0f, 0.0f, -150.0f));
    models[AXIS_SUPPORT_1].setPosition(glm::vec3(-112.0f, 0.0f, -150.0f));
    models[AXIS_SUPPORT_2].setPosition(glm::vec3(-70.0f, 0.0f, 150.0f));
    models[AXIS_SUPPORT_3].setPosition(glm::vec3(-112.0f, 0.0f, 150.0f));
    models[AXIS_0].setPosition(glm::vec3(-70.0f, 20.0f, 0.0f));
    models[AXIS_1].setPosition(glm::vec3(-112.0f, 20.0f, 0.0f));
    models[LINEAR_BEARING_0].setPosition(glm::vec3(-70.0f, 31.0f, -20.0f));
    models[LINEAR_BEARING_1].setPosition(glm::vec3(-70.0f, 31.0f, 20.0f));
    models[LINEAR_BEARING_2].setPosition(glm::vec3(-112.0f, 31.0f, -20.0f));
    models[STEPPER_MOTOR_0].setPosition(glm::vec3(-160.0f, 20.0f, -130.0f));
    models[PLATFORM_0].setPosition(glm::vec3(-90.0f, 32.0f, 0.0f));
    models[PLATFORM_1].setPosition(glm::vec3(-117.0f, 100.0f, 32.0f));
    models[SERVOMOTOR].setPosition(glm::vec3(-110.0f, 80.0f, 8.0f));
    models[RACK].setPosition(glm::vec3(-150.0f, 100.0f, 10.0f));
    models[ULTRASSONIC_SENSOR].setPosition(glm::vec3(-25.0f, 100.0f, 10.0f));
    models[BARRIER].setPosition(glm::vec3(170.0f, 0.0f, 0.0f));

    // Sets the models initial rotations
    models[LINEAR_BEARING_0].setRotation(180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    models[LINEAR_BEARING_1].setRotation(180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    models[LINEAR_BEARING_2].setRotation(180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    models[PLATFORM_0].setRotation(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    // Sets the models initial scales
    models[PLATFORM_0].setScale(glm::vec3(-1.0f, 1.0f, 1.0f));
    models[PLATFORM_1].setScale(glm::vec3(1.0f, 1.0f, -1.0f));
    models[ULTRASSONIC_SENSOR].setScale(glm::vec3(1.0f, 1.0f, -1.0f));
}

// Updates the models positions
void Scene::updatePosition(glm::vec3 keyPosition)
{
    models[LINEAR_BEARING_0].setPosition(glm::vec3(-70.0f, 31.0f, keyPosition.x/2 - 120.0f));
    models[LINEAR_BEARING_1].setPosition(glm::vec3(-70.0f, 31.0f, keyPosition.x/2 - 80.0f));
    models[LINEAR_BEARING_2].setPosition(glm::vec3(-112.0f, 31.0f, keyPosition.x/2 - 120.0f));
    models[PLATFORM_0].setPosition(glm::vec3(-90.0f, 32.0f, keyPosition.x/2 - 100.0f));
    models[PLATFORM_1].setPosition(glm::vec3(-117.0f, keyPosition.y/2 + 100.0f, keyPosition.x/2 - 68.0f));
    models[SERVOMOTOR].setPosition(glm::vec3(-110.0f, keyPosition.y/2 + 80.0f, keyPosition.x/2 - 92.0f));
    models[RACK].setPosition(glm::vec3(-30 - 6*keyPosition.z, keyPosition.y/2 + 100.0f, keyPosition.x/2 - 90.0f));
    models[ULTRASSONIC_SENSOR].setPosition(glm::vec3(95.0f - 6*keyPosition.z, keyPosition.y/2 + 100.0f, keyPosition.x/2 - 90.0f));
}

// Draws all the models in the scene
void Scene::drawScene()
{
    // Updates the camera
	camera->updateMatrix();

    // Draws each model
    for(int i=0; i<models.size(); i++)
    {
        models[i].draw(*camera);
    }
}

// Deallocates memory
void Scene::destroy()
{
    delete this->defaultShader;
}

// Creates a model
Model Scene::createModel(const char* modelName)
{
    std::string path(modelName);
    path.append("/");
    path.append(modelName);
    path.append(".gltf");

    const char* modelPath = path.c_str();

    return Model(modelPath, *defaultShader);
}
