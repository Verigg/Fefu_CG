#pragma once

#include "res/func.h"

//#include "gui.cpp"

#include "res/texture.h"
#include "res/mesh.h"
#include "res/camera.h"
#include "res/skybox.h"
using namespace std;

int main() {
	// setup window, glew, imgui
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT, 32), "First Window",
		sf::Style::Titlebar | sf::Style::Close, default_settings());

	window.setVerticalSyncEnabled(true);
	window.setActive();

	glewExperimental = GL_TRUE; 

	if (GLEW_OK != glewInit()) { 
		cout << "Error:: glew not init =(" << endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	ImGui::SFML::Init(window);




	Shader cube("shaders/texture.vs", "shaders/texture.fs");
	Shader light("shaders/point.vs", "shaders/point.fs");

	Texture face("images/1.png");
	cube.Use();
	cube.SetInt("material.diffuse", 1);
	cube.SetInt("material.specular", 1);


	Shader skybox_shader("shaders/skybox/skybox.vs", "shaders/skybox/skybox.fs");
	std::string path = "images/skybox/rainbow_";
	std::vector<std::string> faces{
		path + "lf.png",
		path + "rt.png",
		path + "dn.png",
		path + "up.png",
		path + "ft.png",
		path + "bk.png"
	};
	Texture sky(faces);
	skybox_shader.Use();
	skybox_shader.SetInt("skybox",0);
	Skybox skybox(skybox_shader);
	Mesh box("models/box2.obj");
	Mesh cylinder("models/cylinder.obj");

	camera camera;

	Mat4 model(1.0f);
	Mat4 projection = model.perspective(radians(45.0f), static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 1000.0f);
	cube.SetMat4("projection", projection);
	
	Vec3 pos_light_cube(1.2f, 0.0f, 2.0f);

	Vec3 pos_light_cube_two(1.2f, 0.0f, -4.0f);

	//


	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };
	sf::Clock deltaClock;
	int alpha = 0;
	bool isGo = true;
	while (isGo) {
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent)) {

			switch (windowEvent.type)
			{
			case sf::Event::Closed:
				isGo = false;
				break;
			case sf::Event::KeyPressed:
				camera.KeyboardInput();
				break;
			case sf::Event::MouseMoved:
				camera.update_view(window);
				break;
			default:
				break;
			}
		}
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		cube.Use();
		cube.SetVec3("viewPos", camera.GetPos());
		cube.SetFloat("material.shininess", shininess);

		cube.SetVec3("dirLight.direction", Vec3(-0.2f, -1.0f, -0.3f));
		cube.SetVec3("dirLight.ambient", Vec3(0.05f, 0.05f, 0.05f));
		cube.SetVec3("dirLight.diffuse", Vec3(0.4f, 0.4f, 0.4f));
		cube.SetVec3("dirLight.specular", Vec3(0.5f, 0.5f, 0.5f));

		cube.SetVec3("pointLights[0].position", pos_light_cube * 3);
		cube.SetVec3("pointLights[0].ambient", Vec3(0.05f, 0.05f, 0.05f)*30);
		cube.SetVec3("pointLights[0].diffuse", Vec3(0.8f, 0.8f, 0.8f));
		cube.SetVec3("pointLights[0].specular", specular);
		cube.SetFloat("pointLights[0].constant", constant);
		cube.SetFloat("pointLights[0].linear", linear);
		cube.SetFloat("pointLights[0].quadratic", quadratic);

		cube.SetVec3("pointLights[1].position", pos_light_cube_two*4);
		cube.SetVec3("pointLights[1].ambient", Vec3(0.05f, 0.05f, 0.05f));
		cube.SetVec3("pointLights[1].diffuse", Vec3(0.8f, 0.8f, 0.8f));
		cube.SetVec3("pointLights[1].specular", specular);
		cube.SetFloat("pointLights[1].constant", constant);
		cube.SetFloat("pointLights[1].linear", linear);
		cube.SetFloat("pointLights[1].quadratic", quadratic);

		cube.SetVec3("spotLight.position", camera.GetPos());
		cube.SetVec3("spotLight.direction", camera.GetFront());
		cube.SetVec3("spotLight.ambient", Vec3(0.0f, 0.0f, 0.0f));
		cube.SetVec3("spotLight.diffuse", Vec3(1.0f, 1.0f, 1.0f)); 
		cube.SetVec3("spotLight.specular", specular);
		cube.SetFloat("spotLight.constant", constant);
		cube.SetFloat("spotLight.linear", linear);
		cube.SetFloat("spotLight.quadratic", quadratic);
		cube.SetFloat("spotLight.cutOff", cos(radians(12.5f)));
		cube.SetFloat("spotLight.outerCutOff", cos(radians(15.0f)));
		////
		//face.Bind(0);
		
		box.Draw(light, camera, pos_light_cube*3);
		box.Draw(light, camera, pos_light_cube_two*4);

		box.Draw(cube, camera, { 5.f, 0.f, -5.f });

		box.Draw(cube, camera, { 15.f, 0.f, -5.f }, -alpha, { 0.f, 0.f, -1.f });

		box.Draw(cube, camera, { 25.f, sin(alpha/30.f)*10.f, -5.f}, -alpha, {0.f, 0.f, -1.f});

		cylinder.Draw(cube, camera, { 35.f, 0.f, -5.f });

		cylinder.Draw(cube, camera, { 45.f, 0.f, -5.f }, -alpha, { 1.f, 0.f, -1.f });

		cylinder.Draw(cube, camera, { 55.f, tan(alpha / 30.f) * 10.f, -5.f }, -alpha, { 0.f, 1.f, 0.f });

		alpha = (alpha + 1) % 360;

		skybox.Draw(skybox_shader, camera);


		window.display();
	}


	window.close();
	return 0;
}