#pragma once
#include <entt/entity/fwd.hpp>
#include <imgui-SFML.h>
#include "box2d/types.h"

#include "comp/RenderScene.h"
#include "comp/TextureManager.h"
#include <comp/minerals/Asteroid.h>

using namespace sf;

class creator
{
public:
	static RenderScene makeRenderScene(entt::registry&);
	static TextureManager makeTextureManager(entt::registry&);

	static void makeWorld(entt::registry&);

	static entt::entity makePlayer(entt::registry&, b2Vec2 pos = b2Vec2_zero);

	static entt::entity makeAncientMiningDrone(entt::registry&, entt::entity station = entt::null, b2Vec2 pos = b2Vec2_zero);
	static entt::entity makeAncientMiningDroneStation(entt::registry&, b2Vec2 pos = b2Vec2_zero);
	// ¬озвращает ентити основной базы дронов
	static entt::entity makeComposition_MiningAntientDrones(entt::registry&, b2Vec2 pos = b2Vec2_zero);

	static entt::entity makeAsteroid(entt::registry&, Ore::OreType = Ore::STONE, b2Vec2 pos = b2Vec2_zero);

};

