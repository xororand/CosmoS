#pragma once
#include <entt/entity/fwd.hpp>

class physics
{
public:
	static void step();

private:
	static void stepWorld();
	static void stepBodys();
};

