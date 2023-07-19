#pragma once
#include "Includes.h"
class camera {
public:
	float CameraYaw = -90.0f;
	float CameraPitch = 0.0f;
	Vec3 up;
	Vec3 front;
	Vec3 right;
	Vec3 CameraPosition = {0.f, 0.f, 0.f};
	float speed = 0.2f;

	camera() = default;


	void update_view(sf::RenderWindow& window ) {
		float speed = 0.1f;
		static sf::Vector2i prevPos, curPos, temp, temp2;
		static sf::Vector2i zero = { 0,0 };
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			temp2 = sf::Mouse::getPosition(window);
			if (temp != zero) {
				curPos += temp2 - temp;
				temp = temp2;
			}
			else {
				temp = sf::Mouse::getPosition(window);
			}
		}
		else {
			temp = zero;
			temp2 = zero;
		}
		auto dxy = (curPos - prevPos);

		prevPos = curPos;

		CameraYaw += static_cast<float>(dxy.x) * speed;
		CameraPitch += static_cast<float>(-dxy.y) * speed;

		if (CameraPitch > 89.0f)
			CameraPitch = 89.0f;
		if (CameraPitch < -89.0f)
			CameraPitch = -89.0f;

		front.x = cos(radians(CameraYaw)) * cos(radians(CameraPitch));
		front.y = sin(radians(CameraPitch));
		front.z = sin(radians(CameraYaw)) * cos(radians(CameraPitch));
		front = normalize(front);
		right = cross(front, Vec3(0.0f, 1.0f, 0.0f)).normalize();
		up = normalize(cross(right, front));
	};

	Mat4 GetProjectionMatrix() {
		Mat4 projection;
		return projection.perspective(radians(45.0f), 1920.0f / 1080.0f, 0.1f, 500.0f);
	}

	Mat4 GetViewMatrix() {
		Mat4 view;
		view = lookAt(CameraPosition, CameraPosition + front, up);
		return view;
	}

	Mat4 ViewForSkybox() {
		Mat4 view = GetViewMatrix();
		view.matrix[3][0] = 0;
		view.matrix[3][1] = 0;
		view.matrix[3][2] = 0;
		view.matrix[3][3] = 0;

		return view;
	}

	void KeyboardInput() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			CameraPosition += front * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			CameraPosition -= front * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			CameraPosition -= right * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			CameraPosition += right * speed;
		}
	}

	Vec3 GetPos() {
		return CameraPosition;
	}

	Vec3 GetFront() {
		return front;
	}

};
