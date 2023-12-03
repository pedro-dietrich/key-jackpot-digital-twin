#include "SerialReceiver.hpp"
#include "SerialTransmitter.hpp"

// Handles serial the port, transmition and reception
class SerialPort
{
    public:
        // Creates and sets up the serial port
        SerialPort(asio::io_context& ioContext, const char* port, Scene& scene);
        // Deallocates memory
        void destroy();

        // Initiates a continuous serial reading in parallel
        void startListening();
        // Stops the serial reading
        void stopListening();

        // Polls any completed asynchronous operations
        void poll();

        // Gets the serial transmitter
        SerialTransmitter* getSerialTransmitter();

    private:
        // Context and port name
        asio::io_context* ioContext;
        const char* portName;

        // Serial port object
        asio::serial_port serialPort;
        // Timeout
        asio::steady_timer steadyTimer;

        // Receiver
        SerialReceiver* serialReceiver;
        // Transmitter
        SerialTransmitter* serialTransmitter;
};
