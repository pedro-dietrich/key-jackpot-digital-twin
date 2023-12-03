#include <iostream>
#include <asio.hpp>

#include "Helpers/FileHandler.hpp"
#include "Window/Window.hpp"
#include "Window/KeyInput.hpp"
#include "Camera/Camera.hpp"
#include "Scene/Scene.hpp"
#include "Serial/SerialPort.hpp"

int main(int argc, char** argv)
{
	// Port to be used for serial communication (COM6 set as default)
	const char* serialPortName = "COM6";

	// Sets the path for the executable and the port for serial communication
	if(argc < 1)
		return -1;
	FileHandler::setRootPath(argv[0]);
	if(argc > 1)
		serialPortName = argv[1];

	// Create window
	Window* window = Window::getWindowInstance();
	// Creates the default shader program
	ShaderProgram defaultShader("Default.vert", "Default.frag");
	// Creates camera
	Camera camera;
	// Creates a KeyInput object to handle input
	KeyInput keyInput(&camera);

	// Creates the scene with the project structure
	Scene scene(camera);

	// Creates serial communication handler
	SerialPort* serialPort = nullptr;
	asio::io_context ioContext;
	try
	{
		serialPort = new SerialPort(ioContext, serialPortName, scene);
		serialPort->startListening();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Failed to start serial communication." << std::endl;
		std::cerr << e.what() << std::endl;
	}

	// Enables depth test to only render the closest surface
	glEnable(GL_DEPTH_TEST);

	// Main while loop
	while(window->manageWindow())
	{
		// Specifies a new background color, cleans the back and depth buffers and assigns a new color to it
		glClearColor(0.06f, 0.12f, 0.20f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handles inputs
		keyInput.handleInputs();

		// Handles serial communication if available
		if(serialPort != nullptr)
		{
			serialPort->poll();
			keyInput.handleSerialInputs(serialPort->getSerialTransmitter());
		}

		// Draws the scenary
		scene.drawScene();

		// Handles window events
		window->updateWindow();
	}

	// Stops the serial reading
	if(serialPort != nullptr)
		serialPort->stopListening();
	// Deallocates resources
	scene.destroy();

	return 0;
}
