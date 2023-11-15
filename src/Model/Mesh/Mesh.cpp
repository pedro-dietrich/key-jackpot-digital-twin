#include "Mesh.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VBO.hpp"
#include "EBO.hpp"

// Creates a mesh
Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures, ShaderProgram& shader)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->shaderProgram = &shader;

    generateMeshObjects();
}

// Draws the mesh on the screen
void Mesh::draw(glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
{
    // Tells OpenGL which shader program to use
    shaderProgram->activate();

    // Binds the VAO to be texturized
    vao.bind();

    // Assigns the textures and binds them to be rendered
    for(int i=0; i<textures.size(); i++)
    {
        textures[i].textureUnit(*shaderProgram, "diffuse", i);
        textures[i].bind();
    }

    // Creates the translation matrix and gets the export location
    glm::mat4 translation_mat4 = glm::mat4(1.0f);
    translation_mat4[3] = glm::vec4(translation, 1.0f);
    GLint translation_location = glGetUniformLocation(shaderProgram->ID, "translation");

    // Creates the rotation matrix and gets the export location
    glm::mat4 rotation_mat4 = glm::mat4_cast(rotation);
    GLint rotation_location = glGetUniformLocation(shaderProgram->ID, "rotation");

    // Creates the scale matrix and gets the export location
    glm::mat4 scale_mat4 = glm::scale(scale);
    GLuint scale_location = glGetUniformLocation(shaderProgram->ID, "scale");

    // Exports the transformation matrices to the vertex shader
    glUniformMatrix4fv(translation_location, 1, GL_FALSE, glm::value_ptr(translation_mat4));
    glUniformMatrix4fv(rotation_location, 1, GL_FALSE, glm::value_ptr(rotation_mat4));
    glUniformMatrix4fv(scale_location, 1, GL_FALSE, glm::value_ptr(scale_mat4));

    // Draws the mesh triangles using the GL_TRIANGLES primitive
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao.unbind();
}

void Mesh::destroy()
{
    vao.destroy();
}

// Generates the VBO and the EBO, linking them to the VAO
void Mesh::generateMeshObjects()
{
    vao.bind();

    // Creates the VBO and EBO
    VBO vbo(vertices);
    EBO ebo(indices);

    vbo.bind();
    ebo.bind();

    // Fetches the location for aPos and aTex attributes in the shader program
    GLint posLocation = glGetAttribLocation(shaderProgram->ID, "aPos");
    GLuint texLocation = glGetAttribLocation(shaderProgram->ID, "aTex");

    // Links VBO attributes (vertex and texture coordinates) to the VAO
    vao.linkAttribute(vbo, posLocation, 3, GL_FLOAT, sizeof(Vertex), (void*) 0);
    vao.linkAttribute(vbo, texLocation, 2, GL_FLOAT, sizeof(Vertex), (void*) (3*sizeof(float)));
}
