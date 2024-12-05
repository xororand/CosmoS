#pragma once
#include "../defines.h"
#include "../includes.h"

class game
{
private:
	entt::registry reg;
public:
	game();
	~game();

	int run();
};

