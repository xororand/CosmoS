#pragma once

#include "ChunkCoord.h"

// ��������� ��� ���������, ������� ��������� � �����
struct ChunkMember {
    ChunkCoord coord;
    bool is_static = false;
};