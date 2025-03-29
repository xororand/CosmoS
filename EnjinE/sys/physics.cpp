#include "physics.h"

#include "core/game/game.h"

#include <entt/entity/registry.hpp>
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"

#include "comp/World.h"
#include "comp/Controllable.h"
#include <comp/RenderScene.h>

void physics::step() {
	stepWorld();
	stepBodys();
}

void physics::stepWorld()
{
	// »щем первый попавшийс€ мир
	const auto view = game::reg.view<World, b2WorldId>();
	if (view.begin() == view.end()) return;

	World world = view.get<World>(view.front());
	b2WorldId wid = view.get<b2WorldId>(view.front());
	
	b2World_Step(wid, world.timeStep, world.SubStepCount);
}

void physics::stepBodys()
{
	const auto view = game::reg.view<b2BodyId>();
	for (const auto e : view) {
		b2Vec2 vdelta = b2Vec2_zero;
		b2BodyId bid = view.get<b2BodyId>(e);

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
