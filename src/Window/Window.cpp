#include "Window.hpp"

#include <iostream>

// Unique window instance
Window* Window::windowInstance = nullptr;

// Private window constructor
Window::Window()
{
    // Initializes GLFW
	glfwInit();

	// Informs GLFW that it is being used OpenGL 2.1
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // Does not allow resize (it would stretch the image)
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Sets the window dimensions
    Window::width = 800;
    Window::height = 800;

	// Creates a 800x800 window
	glfwWindow = glfwCreateWindow(width, height, "Key Jackpot - Digital Twin", NULL, NULL);

	// Tests if the window has been successfully created
	checkWindowCreation();

	// Introduces the window into the current context
	glfwMakeContextCurrent(glfwWindow);

	// Initializes GLAD
	gladLoadGL();

    // Normalizes window coordinates
	glViewport(0, 0, width, height);
}

// Gets the only window instance
Window* Window::getWindowInstance()
{
    if(windowInstance == nullptr)
    {
        windowInstance = new Window();
    }

    return windowInstance;
}

// Swaps buffers and handle window events
void Window::updateWindow()
{
    glfwSwapBuffers(glfwWindow);
    glfwPollEvents();
}

// Checks if the window was successfully created
void Window::checkWindowCreation()
{
    if(glfwWindow == NULL)
    {
        std::cerr << "Failed to create window!" << std::endl;
        glfwTerminate();
    }
}

// Decides whether the window should close or not
bool Window::manageWindow()
{
    if(glfwWindowShouldClose(glfwWindow))
    {
        terminate();
        return false;
    }

    return true;
}

// Destroys window and and terminates GLFW
void Window::terminate()
{
    glfwDestroyWindow(glfwWindow);
	glfwTerminate();
}
