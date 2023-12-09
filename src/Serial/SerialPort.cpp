#include "SerialPort.hpp"

#include <iostream>

// Creates and sets up the serial port
SerialPort::SerialPort(asio::io_context& ioContext, const char* port, Scene& scene)
    : serialPort(ioContext, port), steadyTimer(ioContext)
{
    try
    {
    // Saves the context and port name
    this->ioContext = &ioContext;
    this->portName = port;

    // Configures the serial port
    asio::serial_port_base::character_size charSize(7);
    asio::serial_port_base::parity parity(asio::serial_port_base::parity::odd);
    asio::serial_port_base::stop_bits stopBits(asio::serial_port_base::stop_bits::one);
    asio::serial_port_base::baud_rate baudRate(115200);
    asio::serial_port_base::flow_control flowControl(asio::serial_port_base::flow_control::none);
    serialPort.set_option(charSize);
    serialPort.set_option(parity);
    serialPort.set_option(stopBits);
    serialPort.set_option(baudRate);
    serialPort.set_option(flowControl);

    // Creates instances of the receiver and transmitter
    serialReceiver = new SerialReceiver(&serialPort, &steadyTimer, &scene);
    serialTransmitter = new SerialTransmitter(&serialPort);
    }
    catch(const std::exception e)
    {
        std::cerr << "An error has occurred when setting up the serial port:" << std::endl;
        std::cerr << e.what() << std::endl;
    }
}

// Deallocates memory
void SerialPort::destroy()
{
    delete serialReceiver;
    delete serialTransmitter;
}

// Initiates a continuous serial reading in parallel
void SerialPort::startListening()
{
    try
    {
		serialReceiver->readAsync();
	}
	catch(const std::exception e)
	{
		std::cerr << "Serial communication error: " << e.what() << std::endl;
		std::cerr << "Port used: " << portName << std::endl;
	}
}

// Stops the serial reading
void SerialPort::stopListening()
{
    ioContext->stop();
}

// Polls any completed asynchronous operations
void SerialPort::poll()
{
    ioContext->poll();
}

// Gets the serial transmitter
SerialTransmitter* SerialPort::getSerialTransmitter()
{
    return serialTransmitter;
}
