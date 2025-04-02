#include "physics.h"

#include "core/game/game.h"

#include <entt/entity/registry.hpp>
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"

#include "comp/worlds/World.h"
#include "comp/Controllable.h"
#include <comp/RenderScene.h>
#include <comp/worlds/ChunkMember.h>

void physics::step() {
	stepWorlds();
	stepBodys();
}

void physics::stepWorlds() {
	const auto view = game::reg.view<World, b2WorldId>();
	for (const auto e : view) {
		World world = view.get<World>(e);
		b2WorldId wid = view.get<b2WorldId>(e);

		b2World_Step(wid, world.timeStep, world.SubStepCount);
	}
}

void physics::stepBodys() {
	const auto view = game::reg.view<b2BodyId, ChunkMember>();
	for (const auto e : view) {
		ChunkMember& cm = view.get<ChunkMember>(e);

		b2Vec2 vdelta = b2Vec2_zero;
		b2BodyId bid = view.get<b2BodyId>(e);
		b2Vec2 pos = b2Body_GetPosition(bid);
		
		if (auto ctrla = game::reg.try_get<Controllable>(e); ctrla) {
			const float speed = 10000.0f;
			if (ctrla->w) vdelta.y -= 1.0f * speed;
			if (ctrla->s) vdelta.y += 1.0f * speed;
			if (ctrla->a) vdelta.x -= 1.0f * speed;
			if (ctrla->d) vdelta.x += 1.0f * speed;
		}

		if (vdelta != b2Vec2_zero)
			b2Body_ApplyForce(bid, vdelta, b2Body_GetWorldPoint(bid, b2Body_GetPosition(bid)), true);
		else {
			b2Vec2 vel = b2Body_GetLinearVelocity(bid);
			b2Body_SetLinearVelocity(bid, b2Vec2(vel.x * 0.99f, vel.y * 0.99f));
		}
	}
}
