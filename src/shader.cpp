#include "shader.hpp"
#include <cstdio>
#include <map>
#include <string>

std::map<GLuint, std::string> shaderTypeMap = {
    {GL_VERTEX_SHADER, "VERTEX"},
    {GL_FRAGMENT_SHADER, "FRAGMENT"},
    {GL_GEOMETRY_SHADER, "GEOMETRY"}};

Shader::Shader() : Id(0) {}

Shader& Shader::use()
{
    glUseProgram(this->Id);
    return *this;
}

void Shader::compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
    unsigned int sVertex, sFragment, gShader;

    // Vertex Shader
    sVertex = compileShader(vertexSource, GL_VERTEX_SHADER);
    // Fragment Shader
    sFragment = compileShader(fragmentSource, GL_FRAGMENT_SHADER);
    // If geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        gShader = compileShader(geometrySource, GL_GEOMETRY_SHADER);
    }

    // Shader Program
    this->Id = glCreateProgram();
    glAttachShader(this->Id, sVertex);
    glAttachShader(this->Id, sFragment);
    if (geometrySource != nullptr)
    {
        glAttachShader(this->Id, gShader);
    }
    glLinkProgram(this->Id);
    checkCompileErrors(this->Id, "PROGRAM");

    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
    {
        glDeleteShader(gShader);
    }
}

void Shader::setFloat(const char* name, float value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform1f(glGetUniformLocation(this->Id, name), value);
}

void Shader::setInteger(const char* name, int value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform1i(glGetUniformLocation(this->Id, name), value);
}

void Shader::setVector2f(const char* name, float x, float y, bool useShader)
{
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->Id, name), x, y);
}

void Shader::setVector2f(const char* name, const glm::vec2& value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->Id, name), value.x, value.y);
}

void Shader::setVector3f(const char* name, float x, float y, float z, bool useShader)
{
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->Id, name), x, y, z);
}

void Shader::setVector3f(const char* name, const glm::vec3& value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->Id, name), value.x, value.y, value.z);
}

void Shader::setVector4f(const char* name, float x, float y, float z, float w, bool useShader)
{
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->Id, name), x, y, z, w);
}

void Shader::setVector4f(const char* name, const glm::vec4& value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->Id, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const char* name, const glm::mat4& matrix, bool useShader)
{
    if (useShader)
        this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->Id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

#pragma region privates

unsigned int Shader::compileShader(const char* source, GLuint type)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);
    checkCompileErrors(id, shaderTypeMap[type].c_str());

    return id;
}

void Shader::checkCompileErrors(unsigned int object, const char* type)
{
    int success;
    char infoLog[1024];
    if (strcmp(type, "PROGRAM") != 0)
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            fprintf(stderr, "ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n", type, infoLog);
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            fprintf(stderr, "ERROR::PROGRAM_LINKING_ERROR of type: %s\n%s\n", type, infoLog);
        }
    }
}

#pragma endregion