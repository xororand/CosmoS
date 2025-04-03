#pragma once

#include "comp/worlds/ChunkCoord.h"
#include "comp/worlds/ChunkData.h"
#include "box2d/box2d.h"

class ChunkSystem
{
private:
	static constexpr int CHUNK_SIZE = 100;
public:
	std::unordered_map<ChunkCoord, ChunkData> chunks;
public:
	static ChunkCoord get_chunk_coords(b2Vec2 pos);
	std::vector<entt::entity> get_chunk_near_objects(ChunkCoord cc, int radius = 1);
	std::vector<entt::entity> get_chunk_objects(ChunkCoord cc);

	void update_chunk_members();
};
