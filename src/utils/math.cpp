#include "math.h"

glm::quat Math::quatFromViewDirection(const glm::vec3& dir) {
    glm::vec3 nd = glm::normalize(dir);

    glm::vec3 euler (
         std::asin(nd.y),
        -std::asin(nd.x),
        0.0f
    );

    return glm::quat(euler);
}

uint32_t Math::nextPowerOf2(uint32_t v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}
