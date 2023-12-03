#include "SerialTransmitter.hpp"

#include <iostream>

// Configures the serial communication setings
SerialTransmitter::SerialTransmitter(asio::serial_port* serialPort)
    : serialPort(serialPort)
{}

// Sends a command character
void SerialTransmitter::sendCharacter(char data)
{
    asio::async_write
    (
        *serialPort,
        asio::buffer(&data, 1),
        [this](const asio::error_code& errorCode, std::size_t)
        {
            if(errorCode)
            {
                std::cerr << "Error writing to serial port: " << errorCode.message() << std::endl;
            }
        }
    );
}
