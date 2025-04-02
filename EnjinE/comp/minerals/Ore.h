#pragma once

#define MAX_ORE_COUNT 100

struct Ore {
	enum OreType {
		STONE,
		IRON,
		COPPER,
		URANIUM,
		last
	};

	OreType type;
	int count = 0;

	float getWeight() {

	}

	static size_t getTexIDbyOreType(entt::registry& reg, OreType t) {
		switch (t) {
		case Ore::STONE:	return game::texmngr.getIDbyName(L"asteroid");
		case Ore::IRON:		return game::texmngr.getIDbyName(L"asteroid-iron");
		case Ore::COPPER:	return game::texmngr.getIDbyName(L"asteroid-copper");
		case Ore::URANIUM:	return game::texmngr.getIDbyName(L"asteroid-uranium");
		}
		return NO_TEXTURE;
	}
	static OreType getRand() {
		return (OreType)(rand() % OreType::last);
	}
};