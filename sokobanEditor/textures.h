#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <map>
#include <string>

extern std::unordered_map<std::string, GLuint> loadedTextures;
extern std::map<std::string, GLuint> allTextures;

GLuint LoadTexture(const char* filename);
void LoadAllTextures();
