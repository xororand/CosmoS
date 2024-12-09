#pragma once
#include <entt/entity/fwd.hpp>

class physics
{
public:
	static void step(entt::registry&);

private:
	static void stepWorld(entt::registry&);
	static void stepBodys(entt::registry&);
};

