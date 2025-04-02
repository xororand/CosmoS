#pragma once

#include <functional> // для std::hash

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
            // Хорошая хеш-функция с минимумом коллизий
            return ((size_t)c.x << 32) | (size_t)c.y;
        }
    };
}