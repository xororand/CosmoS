#pragma once

#include <functional> // ��� std::hash

struct ChunkCoord {
    int x;
    int y;

    bool operator==(const ChunkCoord& other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
    template<>
    struct hash<ChunkCoord> {
        size_t operator()(const ChunkCoord& c) const {
            // ������� ���-������� � ��������� ��������
            return ((size_t)c.x << 32) | (size_t)c.y;
        }
    };
}