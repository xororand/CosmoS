#pragma once
#include <entt/entity/fwd.hpp>
#include <imgui-SFML.h>

#include "comp/RenderScene.h"
#include "comp/TextureManager.h"
#include <comp/Asteroid.h>

using namespace sf;

class creator
{
public:
	static RenderScene makeRenderScene(entt::registry&);
	static TextureManager makeTextureManager(entt::registry&);

	static void makeWorld(entt::registry&);

	static entt::entity makePlayer(entt::registry&);
	static entt::entity makeAncientMiningDrone(entt::registry&);
	static entt::entity makeAncientMiningDroneStation(entt::registry&);
	static entt::entity makeAsteroid(entt::registry&, Asteroid::AsteroidType);
};

