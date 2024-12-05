#pragma once
#include <entt/entity/fwd.hpp>
#include <imgui-SFML.h>

using namespace sf;

class creator
{
public:
	static RenderWindow* makeWindow(entt::registry&);
	static void makeWorld(entt::registry&);
	static entt::entity makePlayer(entt::registry&);
};

