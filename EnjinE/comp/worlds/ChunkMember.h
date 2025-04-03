#pragma once

#include "ChunkCoord.h"

// Компонент для сущностей, которые находятся в чанке
struct ChunkMember {
    b2WorldId wid;
    ChunkCoord coord;
    bool is_static = false;
};