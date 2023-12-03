#pragma once

#include <asio.hpp>

// Sends commands to the FPGA through serial communication
class SerialTransmitter
{
    public:
        // Configures the serial communication setings
        SerialTransmitter(asio::serial_port* serialPort);

        // Sends a command character
        void sendCharacter(char data);

    private:
        // Object with the serial port information
        asio::serial_port* serialPort;
};
