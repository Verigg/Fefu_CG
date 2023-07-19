#pragma once
#include <iostream>
#include <string>
#include <ctime>
//glew
#include <GL/glew.h>

//sfml
#include <SFML/Window.hpp>

//imgui
#include <SFML/Graphics/RenderWindow.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

//math
#include "3rd/math/math.h"

inline int WIDTH = 1920;
inline int HEIGHT = 1080;

inline Vec3 ambient(0.2f, 0.2f, 0.2f);
inline Vec3 diffuse(0.5f, 0.5f, 0.5f);
inline Vec3 specular(1.0f, 1.0f, 1.0f);

inline float constant = 1.0f;
inline float linear = 0.09f;
inline float quadratic = 0.032f;
inline float shininess = 32.0f;

struct Vertex {
	std::vector< Vec3 > vertices;
	std::vector< Vec2 > uvs;
	std::vector< Vec3 > normals;
	std::vector< unsigned short > indexes;
};