#include "physics.h"

#include <entt/entity/registry.hpp>
#include "box2d/box2d.h"

#include "comp/World.h"

void physics::step(entt::registry&reg) {
	stepWorld(reg);
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
