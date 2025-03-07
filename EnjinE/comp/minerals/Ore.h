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

	static size_t getTexIDbyOreType(TextureManager tm, OreType t) {
		switch (t) {
			case Ore::STONE:	return tm.getIDbyName(L"asteroid");
			case Ore::IRON:		return tm.getIDbyName(L"asteroid-iron");
			case Ore::URANIUM:	return tm.getIDbyName(L"asteroid-uranium");
		}
	}
};