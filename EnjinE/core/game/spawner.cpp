#include "spawner.h"

#include <entt/entity/registry.hpp>
#include "box2d/box2d.h"

#include "comp/Player.h"
#include "comp/World.h"


void spawner::makeWorld(entt::registry&reg) {
	const auto e = reg.create();
	
	b2WorldDef wdef = b2DefaultWorldDef();
	wdef.gravity = b2Vec2_zero;
	wdef.enableSleep = false;
	b2WorldId wid = b2CreateWorld(&wdef);
	
	reg.emplace<World>(e);
	reg.emplace<b2WorldId>(e, wid);
}

entt::entity spawner::makePlayer(entt::registry&reg) {
	const auto e = reg.create();
	reg.emplace<Player>(e);

	reg.emplace<b2BodyId>(e);
}
