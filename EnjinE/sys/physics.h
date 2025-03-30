#pragma once
#include <entt/entity/fwd.hpp>

class physics
{
public:
	static void step();

private:
	static void stepWorlds();
	static void stepBodys();
};

