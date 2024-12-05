#pragma once
#include <entt/entity/fwd.hpp>
#include <imgui-SFML.h>

#include "comp/RenderScene.h"

using namespace sf;

class creator
{
public:
	static RenderScene makeRenderScene(entt::registry&);

	static void makeWorld(entt::registry&);

	static entt::entity makePlayer(entt::registry&);
};

