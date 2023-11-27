#include "Helpers/FileHandler.hpp"
#include "Window/Window.hpp"
#include "Window/KeyInput.hpp"
#include "Camera/Camera.hpp"
#include "Model/Model.hpp"

int main(int argc, char** argv)
{
	// Sets the path for the executable
	if(argc > 0)
		FileHandler::setRootPath(argv[0]);
	else
		return -1;

	// Create window
	Window* window = Window::getWindowInstance();
	// Creates camera
	Camera camera;
	// Creates a KeyInput object to handle input
	KeyInput keyInput(&camera);

	// Creates the default shader program
	ShaderProgram defaultShader("Default.vert", "Default.frag");

	// Creates the models
	Model base("Base/Base.gltf", defaultShader);
	base.setScale(0.04f);

	Model stepperMotor0("StepperMotor0/StepperMotor0.gltf", defaultShader);
	stepperMotor0.setScale(0.1f);
	stepperMotor0.setPosition(glm::vec3(0.0f, 0.7f, 1.5f));

	Model axis0("Axis/Axis.gltf", defaultShader);
	axis0.setScale(0.002f);
	axis0.setPosition(glm::vec3(0.4f, 0.5f, 1.0f));

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
		// Updates camera
		camera.updateMatrix();

		// Draws the models
		base.draw(camera);
		stepperMotor0.draw(camera);
		axis0.draw(camera);

		// Handles window events
		window->updateWindow();
	}

	return 0;
}
