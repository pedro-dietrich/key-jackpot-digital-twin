#include "SerialReceiver.hpp"

#include <iostream>
#include <regex>

// Configures the serial communication setings
SerialReceiver::SerialReceiver(asio::serial_port* serialPort, asio::steady_timer* steadyTimer, Scene* scene)
    : serialPort(serialPort), steadyTimer(steadyTimer), scene(scene)
{}

// Starts to listen to the port
void SerialReceiver::readAsync()
{
    asio::async_read_until
    (
        *serialPort,
        receiveBuffer,
        '#',
        [this](const asio::error_code& errorCode, std::size_t bytesRead)
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
    // Converts the data in the buffer to a string
    std::string receivedData;
    std::istream inStream(&receiveBuffer);
    std::getline(inStream, receivedData, '#');

    std::cout << "Serial data: " << receivedData << '\t';

    // Checks if serial input matches "x123y456z789" format
    std::regex keyRegex(".*x\\d{3}y\\d{3}z\\d{3}.*");

    // Gets the numeric value if input is valid
    if(std::regex_match(receivedData, keyRegex))
    {
        size_t xPos = receivedData.find('x');
        size_t yPos = receivedData.find('y');
        size_t zPos = receivedData.find('z');
        std::string xValue = receivedData.substr(xPos + 1, 3);
        std::string yValue = receivedData.substr(yPos + 1, 3);
        std::string zValue = receivedData.substr(zPos + 1, 3);

        try
        {
            float x = std::stof(xValue);
            float y = std::stof(yValue);
            float z = std::stof(zValue);

            glm::vec3 keyPosition = glm::vec3(x, y, z);

            std::cout << "(" << keyPosition.x << ", " << keyPosition.y << ", " << keyPosition.z << ")" << std::endl;

            // Updates the structure position
            scene->updatePosition(keyPosition);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Invalid arguments:" << std::endl;
            std::cerr << "x = " << xValue << " y = " << yValue << " z = " << zValue << std::endl;
        }
    }
    else
    {
        std::cerr << "Unexpected serial input received: " << receivedData << std::endl;
    }
}
