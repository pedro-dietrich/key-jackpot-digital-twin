#include "Window/Window.hpp"
#include "Window/KeyInput.hpp"
#include "Camera/Camera.hpp"
#include "Model/Model.hpp"

int main()
{
	// Create window
	Window* window = Window::getWindowInstance();
	// Creates camera
	Camera camera;
	// Creates a KeyInput object to handle input
	KeyInput keyInput(&camera);

	// Creates the default shader program
	ShaderProgram defaultShader("../resources/Shaders/Default.vert", "../resources/Shaders/Default.frag");

	// Creates the model for the base of the structure
	Model base("../resources/Models/Base/Base.gltf", defaultShader);
	base.setScale(0.04f);

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

		// Rotates and draws the base
		base.setRotation(glfwGetTime()/4, glm::vec3(0.8f, 0.6f, 0.0f));
		base.draw(camera);

		window->updateWindow();
	}

	return 0;
}
