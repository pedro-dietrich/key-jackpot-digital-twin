#include "SerialReceiver.hpp"

#include <iostream>

// Configures the serial communication setings
SerialReceiver::SerialReceiver(asio::io_context& ioContext, const char* port, Scene* scene)
    : serialPort(ioContext, port), steadyTimer(ioContext), scene(scene)
{
    asio::serial_port_base::character_size charSize(7);
    asio::serial_port_base::parity parity(asio::serial_port_base::parity::odd);
    asio::serial_port_base::baud_rate baudRate(115200);
    serialPort.set_option(charSize);
    serialPort.set_option(parity);
    serialPort.set_option(baudRate);
}

// Starts to listen to the port
void SerialReceiver::readAsync()
{
    asio::async_read
    (
        serialPort,
        asio::buffer(receiveBuffer),
        [this](const asio::error_code& errorCode, std::size_t)
        {
            if(!errorCode)
            {
                processReceivedData();
                readAsync();
            }
            else
            {
                std::cerr << "Error reading from the serial port: " << errorCode.message() << std::endl;
            }
        }
    );
}

// Decodes the received data
void SerialReceiver::processReceivedData()
{
    std::cout << "Serial data: " << receiveBuffer;

    // Gets the numeric value
    std::string receivedData(receiveBuffer);
    size_t xPos = receivedData.find('x');
    size_t yPos = receivedData.find('y');
    size_t zPos = receivedData.find('z');
    std::string xValue = receivedData.substr(xPos + 1, 3);
    std::string yValue = receivedData.substr(yPos + 1, 3);
    std::string zValue = receivedData.substr(zPos + 1, 3);
    glm::vec3 keyPosition = glm::vec3(std::stof(xValue), std::stof(yValue), std::stof(zValue));

    std::cout << "(" << keyPosition.x << ", " << keyPosition.y << ", " << keyPosition.z << ")" << std::endl;

    // Updates the structure position
    scene->updatePosition(keyPosition);
}
