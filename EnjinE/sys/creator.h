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

	static void makeRenderScene();
	static void makeTextureManager();

	static void makeMainWorld();

	static entt::entity makePlayer(entt::entity world, b2Vec2 pos = b2Vec2_zero);

	static entt::entity makeAncientMiningDrone(entt::entity world, entt::entity station = entt::null, b2Vec2 pos = b2Vec2_zero);
	static entt::entity makeAncientMiningDroneStation(entt::entity world, b2Vec2 pos = b2Vec2_zero);
	static entt::entity makeAsteroid(entt::entity world, Ore::OreType = Ore::STONE, b2Vec2 pos = b2Vec2_zero);

	// ¬озвращает ентити основной базы дронов
	static entt::entity makeComposition_MiningAntientDrones(entt::entity world, b2Vec2 pos = b2Vec2_zero);

};

