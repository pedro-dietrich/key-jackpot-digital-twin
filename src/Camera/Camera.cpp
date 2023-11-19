#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

// Camera constructor
Camera::Camera()
{
    viewMode = LOCKED_VIEW;
}

// Changes between the two view modes
void Camera::changeView(ViewMode mode)
{
    // Configures the change to locked view
    if(viewMode != LOCKED_VIEW && mode == LOCKED_VIEW)
    {
        position = glm::vec3(0.0f, 1.0f, 2.0f);
        orientation = glm::normalize(-position);
        positionAngle = 0.0f;
    }

    // Applies the view mode change
    viewMode = mode;
}

// Moves the camera
void Camera::moveCamera(Direction direction)
{
    if(viewMode == FREE_VIEW)   // Free camera movement
    {
        switch(direction)
        {
            case FOWARD:
                position += speed * orientation;
                break;
            case BACKWARD:
                position -= speed * orientation;
                break;
            case LEFT:
                position -= speed * glm::normalize(glm::cross(orientation, upVector));
                break;
            case RIGHT:
                position += speed * glm::normalize(glm::cross(orientation, upVector));
                break;
            case UP:
                position += speed * upVector;
                break;
            case DOWN:
                position -= speed * upVector;
                break;
        }
    }
    else if(viewMode == LOCKED_VIEW)    // Locked camera movement
    {
        switch(direction)
        {
            case LEFT:
                positionAngle -= speed;
                break;
            case RIGHT:
                positionAngle += speed;
                break;
        }
        position = 2.0f * glm::vec3(glm::sin(positionAngle), 0.5f, glm::cos(positionAngle));
        orientation = glm::normalize(-position);
    }
}

// Changes camera rotation state
bool Camera::changeCameraRotationState(bool tabKey)
{
    switch((cameraRotationState << 1) | tabKey)
    {
        case 1:     // State 0 and tab gets pressed
            cameraRotationState = 1;
            break;
        case 2:     // State 1 and tab gets released
            cameraRotationState = 2;
            break;
        case 5:     // State 2 and tab gets pressed
            cameraRotationState = 3;
            break;
        case 6:     // State 3 and tab gets unpressed
            cameraRotationState = 0;
            break;
    }

    // Rotation is enabled for states 1 and 2
    return (cameraRotationState == 1 || cameraRotationState == 2);
}

// Rotates the camera
bool Camera::rotateCamera(float mouseX, float mouseY)
{
    // Only rotates if camera rotation is enabled
    if(cameraRotationState == 1 || cameraRotationState == 2)
    {
        // Rotation around the X and Y axis
        float rotationX = sensitivity * mouseY;
        float rotationY = sensitivity * mouseX;

        if(viewMode == FREE_VIEW)   // Free view
        {
            // Calculates vertical rotation (X axis) and checks if it isn't within 5° from the Y axis
            glm::vec3 newOrientation = glm::rotate(orientation, -rotationX, glm::normalize(glm::cross(orientation, upVector)));
            if(!(glm::angle(newOrientation, upVector) <= 0.087f || glm::angle(newOrientation, -upVector) <= 0.087f))
                orientation = newOrientation;

            // Calculates horizontal rotation (Y axis)
            orientation = glm::rotate(orientation, -rotationY, upVector);
        }
        else if(viewMode == LOCKED_VIEW)    // Locked view
        {
            positionAngle += rotationY;
            position = 2.0f * glm::vec3(glm::sin(positionAngle), 0.5f, glm::cos(positionAngle));
            orientation = glm::normalize(-position);
        }
        // Recenters the cursor
        return true;
    }
    // Doesn't recenters the cursor
    return false;
}

// Updates the camera's transformation matrix value if needed
void Camera::updateMatrix()
{
    // Initialize intermediate transformation matrices
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projectionMatrix = glm::mat4(1.0f);

    // Sets the position and orientation of the camera
    viewMatrix = (viewMode == FREE_VIEW)
        ? glm::lookAt(position, position + orientation, upVector)
        : glm::lookAt(position, originVector, upVector);

    // Sets the FOV, nearest and farthest view distance, adding perspective
    projectionMatrix = glm::perspective(glm::radians(FOV), 1.0f, nearPlane, farPlane);

    // Final transformation matrix
    cameraMatrix = projectionMatrix * viewMatrix;
}

// Exports the tranformation matrix to the vertex shader
void Camera::exportMatrix(ShaderProgram& shader, const char* uniform)
{
    GLint location = glGetUniformLocation(shader.ID, uniform);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}
