#pragma once

#include "ChunkCoord.h"

// ��������� ��� ���������, ������� ��������� � �����
struct ChunkMember {
    b2WorldId wid;
    ChunkCoord coord;
    bool is_static = false;
};