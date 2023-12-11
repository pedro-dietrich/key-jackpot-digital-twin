#pragma once

#include <glm/glm.hpp>

#include "../Model/Mesh/ShaderProgram.hpp"

// Possible view modes for the camera
enum ViewMode
{
    FREE_VIEW,
    LOCKED_VIEW
};

// Directions for camera movement
enum Direction
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Handles the view position, angle and perspective for rendering
class Camera
{
    public:
        // Camera constructor
        Camera();

        // Changes between the two view modes
        void changeView(ViewMode mode);

        // Moves the camera
        void moveCamera(Direction direction);
        // Changes camera rotation state
        bool changeCameraRotationState(bool tabKey);
        // Rotates the camera
        bool rotateCamera(float mouseX, float mouseY);

        // Updates the camera's transformation matrix value if needed
        void updateMatrix();
        // Exports the tranformation matrix to the vertex shader
        void exportMatrix(ShaderProgram& shader, const char* uniform);

    private:
        // Selects the view mode for the camera
        ViewMode viewMode;

        // Camera position, orientation with initial values
        glm::vec3 position = glm::vec3(0.0f, 400.0f, 350.0f);
        glm::vec3 orientation = glm::vec3(0.0f, -0.752576695f, -0.658504608f);
        // Camera tranformation matrix (for perspective)
        glm::mat4 cameraMatrix = glm::mat4(1.0f);

        // Camera speed and sensitivity
        float speed = 0.5f;
        float sensitivity = 1.0f;
        // Camera's field of view (FOV) in degrees, minimum and maximum view distance
        float FOV = 90.0f;
        float nearPlane = 0.1f;
        float farPlane = 1000.0f;
        // Up vector (vertical axis) and origin to be used as references
        const glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
        const glm::vec3 originVector = glm::vec3(0.0f, 0.0f, 0.0f);

        // Current position angle, in radians (for locked view)
        float positionAngle = 0.0f;
        // State for enabling camera rotation
        int cameraRotationState = 0;
};
