#pragma once

#define STANDART_ORE_COUNT 1000

struct Asteroid {
	enum AsteroidType {
		STONE,
		IRON,
		COPPER,
		URANIUM
	};
	AsteroidType type = STONE;
};