#pragma once
#include <entt/entity/fwd.hpp>

class spawner
{
public:
	static void makeWorld(entt::registry&);
	static entt::entity makePlayer(entt::registry&);
};

