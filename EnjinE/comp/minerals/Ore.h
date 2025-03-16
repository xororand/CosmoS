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

	static size_t getTexIDbyOreType(entt::registry& reg, OreType t) {
		const auto tm = reg.view<TextureManager>();
		if (tm.begin() == tm.end()) return -1;
		TextureManager texmngr = reg.get<TextureManager>(tm.front());

		switch (t) {
			case Ore::STONE:	return texmngr.getIDbyName(L"asteroid");
			case Ore::IRON:		return texmngr.getIDbyName(L"asteroid-iron");
			case Ore::URANIUM:	return texmngr.getIDbyName(L"asteroid-uranium");
		}
	}
	float getWeight() {

	}
};