#include "Helpers/FileHandler.hpp"
#include "Window/Window.hpp"
#include "Window/KeyInput.hpp"
#include "Camera/Camera.hpp"
#include "Model/Model.hpp"
#include "Scene/Scene.hpp"

int main(int argc, char** argv)
{
	// Sets the path for the executable
	if(argc > 0)
		FileHandler::setRootPath(argv[0]);
	else
		return -1;

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

		// Draws the scenary
		scene.drawScene();

		// Handles window events
		window->updateWindow();
	}

	// Deallocates resources
	scene.destroy();

	return 0;
}
