#include "physics.h"

#include <entt/entity/registry.hpp>
#include "box2d/box2d.h"

#include "comp/World.h"
#include "comp/Controllable.h"

void physics::step(entt::registry&reg) {
	stepWorld(reg);
	stepControllable(reg);
}

void physics::stepWorld(entt::registry&reg)
{
	// »щем первый попавшийс€ мир
	const auto view = reg.view<World, b2WorldId>();
	if (view.begin() == view.end()) return;

	World world = view.get<World>(view.front());
	b2WorldId wid = view.get<b2WorldId>(view.front());
	
	b2World_Step(wid, world.timeStep, world.SubStepCount);
}

void physics::stepControllable(entt::registry&reg) {
	// »щем первый попавшийс€ контролируемый ентити
	const auto view = reg.view<Controllable, b2BodyId>();
	if (view.begin() == view.end()) return;

	Controllable ctrla = view.get<Controllable>(view.front());
	b2BodyId bid = view.get<b2BodyId>(view.front());

	b2Vec2 vdelta = b2Vec2_zero;
	if (ctrla.w) vdelta.y += 1.0f;
	if (ctrla.s) vdelta.y -= 1.0f;
	if (ctrla.a) vdelta.x -= 1.0f;
	if (ctrla.d) vdelta.x += 1.0f;

	b2Vec2 vel = b2Body_GetLinearVelocity(bid);
	b2Body_SetLinearVelocity(bid, vel + vdelta);
}
