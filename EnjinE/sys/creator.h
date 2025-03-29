#pragma once
#include <entt/entity/fwd.hpp>
#include <imgui-SFML.h>
#include "box2d/types.h"

#include "core/game/game.h"

#include "comp/RenderScene.h"
#include "comp/TextureManager.h"
#include <comp/minerals/Asteroid.h>

using namespace sf;

class creator
{
public:
	static entt::entity retdes(entt::entity);

	static RenderScene makeRenderScene();
	static TextureManager makeTextureManager();

	static void makeWorld();

	static entt::entity makePlayer(b2Vec2 pos = b2Vec2_zero);

	static entt::entity makeAncientMiningDrone(entt::entity station = entt::null, b2Vec2 pos = b2Vec2_zero);
	static entt::entity makeAncientMiningDroneStation(b2Vec2 pos = b2Vec2_zero);
	// ¬озвращает ентити основной базы дронов
	static entt::entity makeComposition_MiningAntientDrones(b2Vec2 pos = b2Vec2_zero);

	static entt::entity makeAsteroid(Ore::OreType = Ore::STONE, b2Vec2 pos = b2Vec2_zero);

};

