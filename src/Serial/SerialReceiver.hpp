#pragma once

#include <asio.hpp>

#include "../Scene/Scene.hpp"

// Receives data from the fisical structure
class SerialReceiver
{
    public:
        // Configures the serial communication setings
        SerialReceiver(asio::io_context& ioContext, const char* port, Scene* scene);

        // Starts to listen to the port
        void readAsync();

    private:
        // Object with the serial port information
        asio::serial_port serialPort;
        // Timer for timeout
        asio::steady_timer steadyTimer;
        // Buffer for received strings
        char receiveBuffer[13];
        // Scene reference
        Scene* scene;

        // Decodes the received data
        void processReceivedData();
};
