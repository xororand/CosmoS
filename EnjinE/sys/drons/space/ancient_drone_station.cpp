#include "ancient_drone_station.h"
#include <entt/entity/registry.hpp>

#include "comp/drons/space/AncientDroneStation.h"

void ancient_drone_station::tick(entt::registry&reg)
{
	const auto view = reg.view<AncientDroneStation>();

	for (auto e : view) {
		AncientDroneStation ads = reg.get<AncientDroneStation>(e);
		
		// TODO: DRONES LOGIC
		for (auto dron : ads.drones) {



		}
	}
}
