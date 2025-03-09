#pragma once

#include <glad/glad.h>

struct Texture2D
{
    unsigned int Id;
    unsigned int Width, Height;
    unsigned int InternalFormat;
    unsigned int ImageFormat;

    unsigned int WrapS;
    unsigned int WrapT;
    unsigned int FilterMin;
    unsigned int FilterMax;

    Texture2D();
    void generate(unsigned int width, unsigned int height, unsigned char *data);
    void bind() const;
};