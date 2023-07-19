#pragma once

#include "textureLoader.h"


#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
//
//#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


inline GLuint LoadTexture(const char* texture_file_path) {
	GLuint textureID = 0;

	glGenTextures(1, &textureID);
	int w = 0, h = 0, c = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* textureData = stbi_load(texture_file_path, &w, &h, &c, STBI_rgb_alpha);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (textureData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(true);
	}
	else {
		std::cout << "ERR texture load";
	}
	glBindTexture(GL_TEXTURE_2D, textureID);
	stbi_image_free(textureData);
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;
};

inline GLuint LoadSkyTexture(std::vector<std::string> faces) {
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int w = 0, h = 0, c = 0;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		stbi_set_flip_vertically_on_load(true);
		unsigned char* textureData = stbi_load(faces[i].c_str(), &w, &h, &c, STBI_rgb_alpha);
		if (textureData)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
			stbi_image_free(textureData);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(textureData);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return textureID;
}