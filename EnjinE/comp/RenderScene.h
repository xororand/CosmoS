#pragma once
#include "core/includes.h"

struct RenderScene {
	bool is_debug_physics = true;

	sf::View view = {};
	RenderWindow* rw;
	sf::Clock deltaClock;
	
	sf::Font mfont;
};