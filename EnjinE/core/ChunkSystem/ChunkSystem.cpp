#include "ChunkSystem.h"
#include <core/game/game.h>
#include <comp/worlds/ChunkMember.h>

ChunkCoord ChunkSystem::get_chunk_coords(b2Vec2 pos)
{
	return {
		static_cast<int>(std::floor(pos.x / CHUNK_SIZE)),
		static_cast<int>(std::floor(pos.y / CHUNK_SIZE)) // Для 2D
	};
}

std::vector<entt::entity> ChunkSystem::get_chunk_near_objects(ChunkCoord cc, int radius)
{
	std::vector<entt::entity> objs;

	for (int dx = -radius; dx <= radius; ++dx) {
		for (int dy = -radius; dy <= radius; ++dy) {
			ChunkCoord search_coord{ cc.x + dx, cc.y + dy };

			for (auto o : chunks[search_coord].objects)
				objs.push_back(o);
		}
	}

	return objs;
}

std::vector<entt::entity> ChunkSystem::get_chunk_objects(ChunkCoord cc)
{
	return chunks[cc].objects;
}

void ChunkSystem::update_chunk_members(b2WorldId wid)
{
	const auto view = game::reg.view<b2BodyId, ChunkMember>();
	for (const auto e : view) {
		ChunkMember& cm = view.get<ChunkMember>(e);
		if (cm.wid.index1 != wid.index1 || cm.wid.revision != wid.revision) continue;

		b2BodyId bid = view.get<b2BodyId>(e);
		b2Vec2 pos = b2Body_GetPosition(bid);

		ChunkCoord cc = ChunkSystem::get_chunk_coords(pos);

		// Если мы по расчетам не в том чанке где были раньше -> выполняем условие
		if (cm.coord != cc) {
			// Добавляем в новом чанке наш объект
			this->chunks[cc].objects.push_back(e);

			// Удаляем со старого чанка наш объект
			this->chunks[cm.coord].objects.erase(
				std::remove(
					this->chunks[cm.coord].objects.begin(),
					this->chunks[cm.coord].objects.end(),
					e),
				this->chunks[cm.coord].objects.end()
			);

			// Обновляем у нашего Ентити координату чанка
			cm.coord = cc;
		}
	}
}