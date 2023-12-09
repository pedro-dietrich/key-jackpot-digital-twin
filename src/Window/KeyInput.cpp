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

// Handles serial inputs
void KeyInput::handleSerialInputs(SerialTransmitter* transmitter)
{
    GLFWwindow* win = window->getGLFWwindow();

    // Game state controls
    if(glfwGetKey(win, GLFW_KEY_I) == GLFW_PRESS)   // I
        transmitter->sendCharacter('i');            // Initiates game
    if(glfwGetKey(win, GLFW_KEY_J) == GLFW_PRESS)   // J
        transmitter->sendCharacter('j');            // Inserts key
    if(glfwGetKey(win, GLFW_KEY_R) == GLFW_PRESS)   // R
        transmitter->sendCharacter('r');            // Resets game

    // Starts key movement
    if(glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS && !directionState[0])      // Up arrow
    {
        transmitter->sendCharacter('w');                // Moves key up
        directionState[0] = true;
    }
    if(glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS && !directionState[1])    // Left arrow
    {
        transmitter->sendCharacter('a');                // Moves key left
        directionState[1] = true;
    }
    if(glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS && !directionState[2])    // Down arrow
    {
        transmitter->sendCharacter('s');                // Moves key down
        directionState[2] = true;
    }
    if(glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS && !directionState[3])   // Right arrow
    {
        transmitter->sendCharacter('d');                // Moves key right
        directionState[3] = true;
    }

    // Ceases key movement
    if(glfwGetKey(win, GLFW_KEY_UP) == GLFW_RELEASE && directionState[0])    // Up arrow released
    {
        transmitter->sendCharacter('W');                // Stop moving key up
        directionState[0] = false;
    }
    if(glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_RELEASE && directionState[1])  // Left arrow released
    {
        transmitter->sendCharacter('A');                // Stop moving key left
        directionState[1] = false;
    }
    if(glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_RELEASE && directionState[2])  // Down arrow released
    {
        transmitter->sendCharacter('S');                // Stop moving key down
        directionState[2] = false;
    }
    if(glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_RELEASE && directionState[3]) // Right arrow released
    {
        transmitter->sendCharacter('D');                // Stop moving key right
        directionState[3] = false;
    }
}
