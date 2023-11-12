#include "ShaderProgram.hpp"

#include <iostream>

#include "../../Helpers/FileHandler.hpp"

// Constructor that builds a shader program from 2 shaders
ShaderProgram::ShaderProgram(const char *vertexFile, const char *fragmentFile)
{
    // Reads the vertex and fragment shaders files and stores them in character arrays
    const char* vertexCode = get_file_contents(vertexFile).c_str();
    const char* fragmentCode = get_file_contents(fragmentFile).c_str();

    // Creates the shader object reference for both shaders
    GLuint vertexShader = createShaderObject(vertexCode, "Vertex Shader");
    GLuint fragmentShader = createShaderObject(fragmentCode, "Fragment Shader");

    // Creates the OpenGL shader program object and gets its reference
    this->ID = glCreateProgram();
    // Attach both shaders to the shader program and links them together
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    // Checks for compilation errors in the shader program
    compileErrors(ID, "Shader Program");

    // Deletes the already used shader objects
    glDeleteShader(vertexShader);
    glDeleteProgram(fragmentShader);
}

// Activates the shader program to allow usage
void ShaderProgram::activate()
{
    glUseProgram(ID);
}

// Deletes the shader program
void ShaderProgram::destroy()
{
    glDeleteProgram(ID);
}

// Creates an OpenGL shader object and returns its reference
GLuint ShaderProgram::createShaderObject(const char* shaderCode, const char* shaderType)
{
    // Creates an OpenGL shader object and gets its reference
    GLuint shaderReference = glCreateShader(GL_VERTEX_SHADER);
    // Attaches the GLSL shader code to the shader object
    glShaderSource(shaderReference, 1, &shaderCode, NULL);
    // Compiles the shader code
    glCompileShader(shaderReference);

    // Checks for compile errors in the vertex shader
    compileErrors(shaderReference, shaderType);

    // Returns the reference
    return shaderReference;
}

// Checks for shader compilation errors
void ShaderProgram::compileErrors(unsigned int shader, const char *type)
{
    // Verify if shader compilation status
    GLint hasCompiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);

    // In case of failure, the error message is printed
    if(hasCompiled == GL_FALSE)
    {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cerr << "Shader compilation error for: " << type << std::endl <<
            "Info log: " << infoLog << std::endl << std::endl;
    }
}
