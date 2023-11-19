#pragma once

#include "Window.hpp"
#include "../Camera/Camera.hpp"

// Receives keyboard inputs and handles it
class KeyInput
{
    public:
        // Constructor
        KeyInput(Camera* camera);

        // Handles all key input functions
        void handleInputs();

    private:
        // Window instance, which receives the keyboard inputs
        Window* window;
        // Camera instance
        Camera* camera;
};
