#pragma once

#include "includes.h"

inline sf:: ContextSettings default_settings() {
	sf::ContextSettings settings;
	settings.depthBits = 24; // количество битов буффера глубины
	settings.stencilBits = 8; //количество битов буфера трафарета
	//settings.majorVersion = 4;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Core;
	//settings.sRgbCapable = true;
	return settings;
}

