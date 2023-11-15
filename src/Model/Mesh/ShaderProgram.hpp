#pragma once

#include <glad/glad.h>

class ShaderProgram
{
    public:
        // Reference ID of the shader program
        GLuint ID;

        // Constructor that builds a shader program from 2 shaders
        ShaderProgram(const char* vertexFile, const char* fragmentFile);

        // Activates the shader program to allow usage
        void activate();
        // Deletes the shader program
        void destroy();

    private:
        // Creates an OpenGL shader object and returns its reference
        GLuint createShaderObject(const char* shaderSource, const char* shaderType, GLuint shaderEnum);

        // Checks for shader compilation errors
        void compileErrors(GLuint shader, const char* type);
};
