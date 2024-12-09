#include "logics.h"
#include <entt/entity/registry.hpp>

#include "sys/ancient_drone_station.h"

void logics::step(entt::registry&reg)
{
	ancient_drone_station::tick(reg);
}
