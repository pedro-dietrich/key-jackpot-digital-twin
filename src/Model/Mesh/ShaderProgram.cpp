#include "ShaderProgram.hpp"

#include <iostream>

#include "../../Helpers/FileHandler.hpp"

// Constructor that builds a shader program from 2 shaders
ShaderProgram::ShaderProgram(const char *vertexFile, const char *fragmentFile)
{
    // Reads the vertex and fragment shaders files and stores them in character arrays
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Creates the shader object reference for both shaders
    GLuint vertexShader = createShaderObject(vertexSource, "Vertex Shader", GL_VERTEX_SHADER);
    GLuint fragmentShader = createShaderObject(fragmentSource, "Fragment Shader", GL_FRAGMENT_SHADER);

    // Creates the OpenGL shader program object and gets its reference
    ID = glCreateProgram();

    // Attach both shaders to the shader program and links them together
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // Checks for compilation errors in the shader program
    compileErrors(ID, "Shader Program");

    // Deletes the already used shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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
GLuint ShaderProgram::createShaderObject(const char* shaderSource, const char* shaderType, GLuint shaderEnum)
{
    // Creates an OpenGL shader object and gets its reference
    GLuint shaderReference = glCreateShader(shaderEnum);
    // Attaches the GLSL shader code to the shader object
    glShaderSource(shaderReference, 1, &shaderSource, nullptr);
    // Compiles the shader code
    glCompileShader(shaderReference);

    // Checks for compile errors in the vertex shader
    compileErrors(shaderReference, shaderType);

    // Returns the reference
    return shaderReference;
}

// Checks for shader compilation errors
void ShaderProgram::compileErrors(GLuint shader, const char* type)
{
    if(type != "Shader Program")
    {
        // Verify the shader compilation status
        GLint compileStatus;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

        if(compileStatus == GL_FALSE)
        {
            char infoLog[1024];
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "Shader compilation error for: " << type << std::endl <<
                "Info log: " << infoLog << std::endl;
        }
    }
    else
    {
        // Verify the shader program linking status
        GLint linkStatus;
        glGetProgramiv(shader, GL_LINK_STATUS, &linkStatus);

        if(linkStatus == GL_FALSE)
        {
            char infoLog[1024];
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "Shader linking error for: " << type << std::endl <<
                "Info log: " << infoLog << std::endl;
        }
    }
}
