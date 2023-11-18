#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Camera constructor
Camera::Camera()
{
    viewMode = FREE_VIEW;
}

// Changes between the two view modes
void Camera::swapView()
{
    if(viewMode == FREE_VIEW)
    {
        viewMode = LOCKED_VIEW;
        position = glm::vec3(0.0f, 1.0f, 2.0f);
        orientation = glm::vec3(0.0f, -1.0f, -1.0f);
    }
    else
    {
        viewMode = FREE_VIEW;
    }
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
