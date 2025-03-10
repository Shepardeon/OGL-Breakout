#include "resourceManager.hpp"

#include <cstdio>
#include <fstream>
#include <sstream>

#include "stb_image.h"

ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return instance;
}

Shader ResourceManager::LoadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath, std::string name)
{
    ResourceManager& instance = GetInstance();
    instance.shaders[name] = instance.loadShaderFromFile(vertexPath, fragmentPath, geometryPath);
    return instance.shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return GetInstance().shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
    ResourceManager& instance = GetInstance();
    instance.textures[name] = instance.loadTextureFromFile(file, alpha);
    return instance.textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return GetInstance().textures[name];
}

void ResourceManager::Clear()
{
    ResourceManager& instance = GetInstance();
    for (auto iter : instance.shaders)
        glDeleteProgram(iter.second.Id);
    for (auto iter : instance.textures)
        glDeleteTextures(1, &iter.second.Id);
}

#pragma region privates

Shader ResourceManager::loadShaderFromFile(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    std::string vertexCode, fragmentCode, geometryCode;

    try
    {
        // open files
        std::ifstream vertexShaderFile(vertexPath);
        std::ifstream fragmentShaderFile(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        // if geometry shader path is present, also load a geometry shader
        if (geometryPath != nullptr)
        {
            std::ifstream geometryShaderFile(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        printf("ERROR::SHADER: Failed to read shader files\n");
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();

    Shader shader;
    shader.compile(vShaderCode, fShaderCode, geometryPath != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
    Texture2D texture;
    if (alpha)
    {
        texture.InternalFormat = GL_RGBA;
        texture.ImageFormat = GL_RGBA;
    }

    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    if (data)
    {
        texture.generate(width, height, data);
    }
    else
    {
        printf("ERROR::TEXTURE: Failed to load texture\n");
        printf("\t- %s\n", stbi_failure_reason());
    }

    stbi_image_free(data);
    return texture;
}

#pragma endregion