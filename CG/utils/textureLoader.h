#pragma once
#include <string>
#include <GL/glew.h>
#include <vector>

inline GLuint LoadTexture(const char* texture_file_path);
inline GLuint LoadSkyTexture(std::vector<std::string> faces);