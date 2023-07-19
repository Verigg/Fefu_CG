#pragma once

#include "includes.h"

inline sf:: ContextSettings default_settings() {
	sf::ContextSettings settings;
	settings.depthBits = 24; // ���������� ����� ������� �������
	settings.stencilBits = 8; //���������� ����� ������ ���������
	//settings.majorVersion = 4;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Core;
	//settings.sRgbCapable = true;
	return settings;
}

