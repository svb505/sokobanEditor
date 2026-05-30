#pragma once
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <unordered_map>
#include <map>
#include <string>
#include "textures.h"

std::unordered_map<std::string, GLuint> loadedTextures;
std::map<std::string, GLuint> allTextures;

GLuint LoadTexture(const char* filename) {
    if (loadedTextures.contains(filename)) return loadedTextures[filename];

    int width = 0;
    int height = 0;
    int channels = 0;

    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

    if (!data) return 0;

    GLenum format = GL_RGB;

    if (channels == 1) format = GL_RED;
    else if (channels == 3) format = GL_RGB;
    else if (channels == 4)format = GL_RGBA;
    else {
        stbi_image_free(data);
        return 0;
    }

    GLuint texture = 0;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    loadedTextures[filename] = texture;

    return texture;
}
void LoadAllTextures() {
    allTextures["box"] = LoadTexture("textures/box.jpg");
    allTextures["boxF"] = LoadTexture("textures/boxF.jpg");
}
