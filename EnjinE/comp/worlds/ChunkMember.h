#pragma once

#include "ChunkCoord.h"

// Компонент для сущностей, которые находятся в чанке
struct ChunkMember {
    ChunkCoord coord;
    bool is_static = false;
};