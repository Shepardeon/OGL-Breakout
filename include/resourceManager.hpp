#pragma once

#include <glad/glad.h>

#include <map>
#include <string>

#include "shader.hpp"
#include "texture.hpp"

struct ResourceManager
{
    static ResourceManager& GetInstance();

    static Shader LoadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath, std::string name);
    static Shader GetShader(std::string name);
    static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
    static Texture2D GetTexture(std::string name);
    static void Clear();

   private:
    ResourceManager() = default;

    static ResourceManager* instance;
    std::map<std::string, Shader> shaders;
    std::map<std::string, Texture2D> textures;

    Shader loadShaderFromFile(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    Texture2D loadTextureFromFile(const char* file, bool alpha);
};