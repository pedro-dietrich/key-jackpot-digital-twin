#pragma once

#include "Window.hpp"
#include "../Camera/Camera.hpp"
#include "../Serial/SerialTransmitter.hpp"

// Receives keyboard inputs and handles it
class KeyInput
{
    public:
        // Constructor
        KeyInput(Camera* camera);

        // Handles all key input functions
        void handleInputs();

        // Handles serial inputs
        void handleSerialInputs(SerialTransmitter* transmitter);

    private:
        // Window instance, which receives the keyboard inputs
        Window* window;
        // Camera instance
        Camera* camera;
};
