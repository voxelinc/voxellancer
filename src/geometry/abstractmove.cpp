#include "acceleration.h"


AbstractMove::AbstractMove():
    AbstractMove(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f))
{
}

AbstractMove::AbstractMove(const glm::vec3& directional, const glm::vec3& angular):
    m_directional(directional),
    m_angular(angular)
{
}

void AbstractMove::clear() {
    m_directional = glm::vec3(0.0f, 0.0f, 0.0f);
    m_angular = glm::vec3(0.0f, 0.0f, 0.0f);
}

const glm::vec3& AbstractMove::directional() const {
    return m_directional;
}

void AbstractMove::setDirectional(const glm::vec3& directional) {
    m_directional = directional;
}

const glm::vec3& AbstractMove::angular() const {
    return m_angular;
}

void AbstractMove::setAngular(const glm::vec3& angular) {
    m_angular = angular;
}

AbstractMove& AbstractMove::operator+=(const AbstractMove& other) {
    m_directional += other.directional();
    m_angular += other.angular();

    return *this;
}

AbstractMove AbstractMove::operator*(const AbstractMove& other) const {
    return AbstractMove(
         m_directional * other.directional(),
         m_angular * other.angular()
    );
}

AbstractMove AbstractMove::operator/(float dividor) const {
    assert(dividor != 0.0f);
    return AbstractMove(
         m_directional / dividor,
         m_angular / dividor
    );
}

