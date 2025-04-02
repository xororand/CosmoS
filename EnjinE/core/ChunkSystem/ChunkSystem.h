#pragma once

#include "comp/worlds/ChunkCoord.h"
#include "comp/worlds/ChunkData.h"
#include "box2d/box2d.h"

class ChunkSystem
{
public:
	static constexpr int CHUNK_SIZE = 512;
	static ChunkCoord get_chunk_coords(b2Vec2 pos) {
		return {
			static_cast<int>(std::floor(pos.x / CHUNK_SIZE)),
			static_cast<int>(std::floor(pos.y / CHUNK_SIZE)) // Äëÿ 2D
		};
	}
	static std::vector<entt::entity> get_chunk_near_objects(ChunkCoord cc, int radius = 1);

	std::unordered_map<ChunkCoord, ChunkData> chunks;

	static void update_chunk_members();
};

