#include "impact.h"


const glm::vec3 &Impact::vec3() const {
    return *this;
}

Impact &Impact::add(const Impact &impact) {
    glm::vec3::operator+=(static_cast<const glm::vec3&>(impact));
    return *this;
}
