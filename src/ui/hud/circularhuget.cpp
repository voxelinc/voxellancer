#include "circularhudget.h"


CircularHudget::CircularHudget() {

}

float CircularHudget::radius() const {
    return m_radius;
}

void CircularHudget::setRadius(float radius) {
    m_radius = radius;
}

const glm::vec3& CircularHudget::position() const {
    return m_position;
}

void CircularHudget::setPosition(const glm::vec3& position) {
    m_position = position;
}

bool CircularHudget::isAt(const glm::quat& quat) const {

}
