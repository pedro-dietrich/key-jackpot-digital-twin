#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Creates and handles the application window
class Window
{
    public:
        // Deletes the copy constructor
        Window(const Window& win) = delete;

        // Gets the only window instance (singleton)
        static Window* getWindowInstance();

        // Decides whether the window should close or not
        bool manageWindow();
        // Swaps buffers and handle window events
        void updateWindow();
        // Closes the window
        void closeWindow();

        // Gets window's width and height
        unsigned int getWidth();
        unsigned int getHeight();
        // Gets GLFW window object
        GLFWwindow* getGLFWwindow();

    private:
        // Window class single instance
        static Window* windowInstance;

        // GLFW's window object
        GLFWwindow* glfwWindow;

        // Tells if window should close or not
        bool windowShouldClose = false;

        // Window's width and height
        unsigned int width;
        unsigned int height;

        // Private constructor
        Window();

        // Checks if the window was successfully created
        void checkWindowCreation();
        // Destroys window and and terminates GLFW
        void terminate();
};
