#include "vmath.h"
#include <cmath>

float vmath::dist(const b2Vec2& a, const b2Vec2& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}