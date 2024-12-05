#pragma once
#include "../defines.h"
#include "../includes.h"

#include "core/grafics/grafics.h"

class game
{
private:
	entt::registry reg;
	GLFWwindow* glfw = nullptr;

	const double fpsLimit = 1.0 / 60.0;
	double lastUpdateTime = 0; 
	double lastFrameTime = 0;
public:
	game();
	~game();

	int run();
};

