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
        GLuint createShaderObject(const char* shaderCode, const char* shaderType);

        // Checks for shader compilation errors
        void compileErrors(unsigned int shader, const char* type);
};
