#pragma once
#include "../defines.h"
#include "../includes.h"

class game
{
public:
	static inline entt::registry reg;
	game();
	~game();

	int run();
};

