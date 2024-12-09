#pragma once

#define MAX_ORE_COUNT 100

struct Ore {
	enum OreType {
		STONE,
		IRON,
		COPPER,
		URANIUM
	};
	OreType type;
	int count = 0;
};