#include "logics.h"
#include <entt/entity/registry.hpp>

#include "sys/drons/space/AncientDroneSystem.h"
#include "comp/worlds/World.h"
#include "box2d/box2d.h"
#include <core/ChunkSystem/ChunkSystem.h>

void logics::step() {
	stepWorlds();
}

void logics::stepWorlds() {
	const auto view = game::reg.view<World, b2WorldId, ChunkSystem>();
	for (const auto e : view) {
		World world = view.get<World>(e);
		b2WorldId wid = view.get<b2WorldId>(e);
		ChunkSystem& cs = view.get<ChunkSystem>(e);

		cs.update_chunk_members();
	}
}
