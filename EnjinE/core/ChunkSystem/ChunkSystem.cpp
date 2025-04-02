#include "ChunkSystem.h"
#include <core/game/game.h>
#include <comp/worlds/ChunkMember.h>

std::vector<entt::entity> ChunkSystem::get_chunk_near_objects(ChunkCoord cc, int radius)
{
	std::vector<entt::entity> objs;

	for (int dx = -radius; dx <= radius; ++dx) {
		for (int dy = -radius; dy <= radius; ++dy) {
			ChunkCoord search_coord{ cc.x + dx, cc.y + dy };

			for (auto o : game::cs.chunks[search_coord].objects)
				objs.push_back(o);
		}
	}

	return objs;
}

void ChunkSystem::update_chunk_members()
{
	const auto view = game::reg.view<b2BodyId, ChunkMember>();
	for (const auto e : view) {
		ChunkMember& cm = view.get<ChunkMember>(e);
		b2BodyId bid = view.get<b2BodyId>(e);
		b2Vec2 pos = b2Body_GetPosition(bid);

		ChunkCoord cc = ChunkSystem::get_chunk_coords(pos);

		// Если мы по расчетам не в том чанке где были раньше -> выполняем условие
		if (cm.coord != cc) {
			// Добавляем в новом чанке наш объект
			game::cs.chunks[cc].objects.push_back(e);
			// Удаляем со старого чанка наш объект
			game::cs.chunks[cm.coord].objects.erase(
				std::remove(
					game::cs.chunks[cm.coord].objects.begin(),
					game::cs.chunks[cm.coord].objects.end(),
					e),
				game::cs.chunks[cm.coord].objects.end()
			);
			// Обновляем у нашего Ентити координату чанка
			cm.coord = cc;
		}
	}
}