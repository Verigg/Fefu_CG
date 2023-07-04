#include <iostream>

//glew
#include <GL/glew.h>

//sfml
#include <SFML/Window.hpp>

//stb
#define STB_IMAGE_IMPLEMENTATION
#include "3rd/stb/stb_image.h"

//math
#include "3rd/math/math.h"

using namespace std;

int main() {
	sf::ContextSettings settings;
	settings.depthBits = 24; // количество битов буффера глубины
	settings.stencilBits = 8; //количество битов буфера трафарета
	settings.majorVersion = 4;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Core;

	sf::Window window(sf::VideoMode(800, 600, 32), "First Window",
		sf::Style::Titlebar | sf::Style::Close);

	glewExperimental = GL_TRUE; // включить все современные функции ogl

	if (GLEW_OK != glewInit()) { // включить glew
		cout << "Error:: glew not init =(" << endl;
		return -1;
	}



	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);

	const char* vshader = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 inPos;\n"
		"layout (location = 1) in vec2 aTexCoords;\n"
		"out vec2 TexCoords;\n"
		"void main() {\n"
		"	 TexCoords = aTexCoords;\n"
		"	 gl_Position = vec4(inPos,1.0);\n"
		"}\n";

	const char* fshader = 
		"#version 330 core\n"
		"in vec2 TexCoords;\n"
		"out vec3 OutColor;\n"
		"uniform sampler2D tex;\n"
		"void main() {\n"
		"	 vec3 rgb = texture(tex, TexCoords).rgb;\n"
		"	 OutColor = rgb;\n"
		"}\n";
	
	unsigned textureID = 0;
	glGenTextures(1, &textureID);


	int w = 0, h = 0, c = 0;
	unsigned char* textureData = stbi_load("./jij.jpg", &w, &h, &c, 0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (textureData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(true);
	} 
	else {
		cout << "ERR";
	}
	stbi_image_free(textureData);
	glBindTexture(GL_TEXTURE_2D, 0);


	int vshaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshaderID, 1, &vshader, nullptr);
	glCompileShader(vshaderID);

	int res = 0;
	glGetShaderiv(vshaderID, GL_COMPILE_STATUS, &res);
	if (!res) {
		char log[512];
		glGetShaderInfoLog(vshaderID, 512, nullptr, log);
		cout << log;
		return 1;
	}

	int fshaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshaderID, 1, &fshader, nullptr);
	glCompileShader(fshaderID);

	glGetShaderiv(fshaderID, GL_COMPILE_STATUS, &res);
	if (!res) {
		char log[512];
		glGetShaderInfoLog(fshaderID, 512, nullptr, log);
		cout << log;
		return 1;
	}

	int shaderID = glCreateProgram();
	glAttachShader(shaderID, vshaderID);
	glAttachShader(shaderID, fshaderID);
	glLinkProgram(shaderID);
	glGetShaderiv(shaderID, GL_LINK_STATUS, &res);
	if (!res) {
		char log[512];
		glGetShaderInfoLog(shaderID, 512, nullptr, log);
		cout << log;
		return 1;
	}
	glDeleteShader(vshaderID);
	glDeleteShader(fshaderID);

	float verts[]{
		0.f, 0.5f, 0.f,				0.5f, -1.0f,
		0.5f, -0.5f, 0.f,			-1.0f, 0.f,
		-0.5f, -0.5f, 0.f,			0.f, 0.f
	};	

	unsigned indes[]{
		0,1,2
	};

	unsigned VAO = 0, VBA = 0, IBA = 0;
	glCreateVertexArrays(1, &VAO);
	glGenBuffers(1, &VBA);
	glGenBuffers(1, &IBA);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBA);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBA);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indes), indes, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);





	bool isGo = true;

	while (isGo) {
		sf::Event windowEvent;

		while (window.pollEvent(windowEvent)) { // обработка ивентов
			switch (windowEvent.type)
			{
			case sf::Event::Closed:
				isGo = false;
				break;
			default:
				break;
			}
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //отчистка экрана
		glClear(GL_COLOR_BUFFER_BIT); //отчистка экрана

		//...
		glUseProgram(shaderID);
		glBindVertexArray(VAO);


		glUniform1i(glGetUniformLocation(shaderID, "tex"), 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		window.display();
	}


	window.close();
	return 0;
}