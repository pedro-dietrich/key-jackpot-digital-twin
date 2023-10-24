#include <iostream>

#include "Window/Window.hpp"

int main()
{
	// Create window
	Window* window = Window::getWindowInstance();

	// Main while loop
	while(window->manageWindow())
	{
		// Specifies a new background color, cleans the back and depth buffers and assigns a new color to it
		glClearColor(0.06f, 0.12f, 0.20f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window->updateWindow();
	}

	return 0;
}
