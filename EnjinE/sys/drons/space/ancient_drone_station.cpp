#include "ancient_drone_station.h"

#include "core/game/game.h"

#include <entt/entity/registry.hpp>

#include "comp/AI/drons/space/AncientDroneStation.h"

void ancient_drone_station::tick()
{
	const auto view = game::reg.view<AncientDroneStation>();

	for (auto e : view) {
		AncientDroneStation ads = game::reg.get<AncientDroneStation>(e);
		
		// TODO: DRONES LOGIC
		for (auto dron : ads.drones) {



		}
	}
}
