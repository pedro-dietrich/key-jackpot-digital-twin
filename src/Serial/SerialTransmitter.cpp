#include "SerialTransmitter.hpp"

#include <iostream>

// Configures the serial communication setings
SerialTransmitter::SerialTransmitter(asio::io_context& ioContext, const char* port)
    : serialPort(ioContext, port)
{
    asio::serial_port_base::character_size charSize(7);
    asio::serial_port_base::parity parity(asio::serial_port_base::parity::odd);
    asio::serial_port_base::baud_rate baudRate(115200);
    serialPort.set_option(charSize);
    serialPort.set_option(parity);
    serialPort.set_option(baudRate);
}

// Sends a command character
void SerialTransmitter::sendCharacter(char data)
{
    asio::async_write
    (
        serialPort,
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
