#include "math.h"

glm::quat Math::quatFromDir(const glm::vec3& dir) {
    glm::vec3 nd = glm::normalize(dir);

    glm::vec3 euler (
         std::asin(nd.y),
        -std::asin(nd.x),
        0.0f
    );

    return glm::quat(euler);
}
