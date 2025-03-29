#include "logics.h"
#include <entt/entity/registry.hpp>

#include "sys/drons/space/ancient_drone_station.h"

void logics::step()
{
	ancient_drone_station::tick();
}
