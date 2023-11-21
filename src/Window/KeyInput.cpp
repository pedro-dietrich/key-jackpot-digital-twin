#include "KeyInput.hpp"

// Key input constructor
KeyInput::KeyInput(Camera* camera)
{
    this->window = Window::getWindowInstance();
    this->camera = camera;
}

// Handles all key input functions
void KeyInput::handleInputs()
{
    GLFWwindow* win = window->getGLFWwindow();

    // View mode
    if(glfwGetKey(win, GLFW_KEY_1) == GLFW_PRESS)   // 1
        camera->changeView(LOCKED_VIEW);            // Changes to locked view
    if(glfwGetKey(win, GLFW_KEY_2) == GLFW_PRESS)   // 2
        camera->changeView(FREE_VIEW);              // Changes to free view

    // Camera movement
    if(glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)               // W
        camera->moveCamera(FORWARD);                            // Moves camera foward
    if(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)               // S
        camera->moveCamera(BACKWARD);                           // Moves camera backward
    if(glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)               // A
        camera->moveCamera(LEFT);                               // Moves camera left
    if(glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)               // D
        camera->moveCamera(RIGHT);                              // Moves camera right
    if(glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS)           // Space
        camera->moveCamera(UP);                                 // Moves camera up
    if(glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)    // Left control
        camera->moveCamera(DOWN);                               // Moves camera down

    // Camera rotation enabling
    if(glfwGetKey(win, GLFW_KEY_TAB) == GLFW_PRESS)     // Tab pressed
        camera->changeCameraRotationState(true)         // Hides cursor if needed
            ? glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN)
            : glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    if(glfwGetKey(win, GLFW_KEY_TAB) == GLFW_RELEASE)   // Tab released
        camera->changeCameraRotationState(false);

    // Gets mouse position
    double mouseX, mouseY;
    glfwGetCursorPos(win, &mouseX, &mouseY);
    // Rotates the camera
    unsigned int halfHeight = window->getHeight() / 2;
    bool recenter = camera->rotateCamera
    (
        (float) (mouseX - halfHeight) / window->getHeight(),
        (float) (mouseY - halfHeight) / window->getHeight()
    );
    // Recenters mouse if needed
    if(recenter)
        glfwSetCursorPos(win, (window->getWidth() / 2), halfHeight);
}