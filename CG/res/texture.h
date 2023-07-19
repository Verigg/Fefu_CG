#pragma once
#include "../utils/textureloader.cpp"

class Texture {
public:

	Texture(char const* path) {
		id = LoadTexture("./images/1.png");
	};

	
	Texture(std::vector<std::string> faces) {
		id = LoadSkyTexture(faces);
	}

	void Bind(int flag = -1) {
		if (flag == 0) {
			glActiveTexture(GL_TEXTURE0);
		}
		if (flag == 1) {
			glActiveTexture(GL_TEXTURE1);
		}
		glBindTexture(GL_TEXTURE_2D, id);
	};

private:
	unsigned int id;
};