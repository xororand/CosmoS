#pragma once
#include "../defines.h"
#include "../includes.h"

#include "spawner.h"

class game
{
private:
	entt::registry reg;
public:
	game();
	~game();

	int run();
};

