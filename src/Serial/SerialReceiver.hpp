#pragma once

#include <asio.hpp>

#include "../Scene/Scene.hpp"

// Receives data from the fisical structure
class SerialReceiver
{
    public:
        // Configures the serial communication setings
        SerialReceiver(asio::serial_port* serialPort, asio::steady_timer* steadyTimer, Scene* scene);

        // Starts to listen to the port
        void readAsync();

    private:
        // Object with the serial port information
        asio::serial_port* serialPort;
        // Timer for timeout
        asio::steady_timer* steadyTimer;
        // Buffer for received strings
        asio::streambuf receiveBuffer;
        // Scene reference
        Scene* scene;

        // Decodes the received data
        void processReceivedData();
};
