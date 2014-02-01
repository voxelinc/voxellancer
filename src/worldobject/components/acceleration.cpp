#include "acceleration.h"


Acceleration::Acceleration():
    Acceleration(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f))
{
}

Acceleration::Acceleration(const glm::vec4& directional, const glm::vec3& angular):
    m_directional(directional),
    m_angular(angular)
{
}

Acceleration::Acceleration(const glm::vec3& directional, const glm::vec3& angular) {
    m_directional = glm::vec4(
        directional.x,
        directional.y,
        directional.z < 0.0f ? directional.z : 0.0f,
        directional.z > 0.0f ? directional.z : 0.0f
    )
    m_angular = angular;
}

void Acceleration::clear() {
    m_directional = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    m_angular = glm::vec3(0.0f, 0.0f, 0.0f);
}

const glm::vec4& Acceleration::directional() const {
    return m_directional;
}

void Acceleration::setDirectional(const glm::vec4& directional) {
    m_directional = directional;
}

const glm::vec3& Acceleration::angular() const {
    return m_angular;
}

void Acceleration::setAngular(const glm::vec3& angular) {
    m_angular = angular;
}

Acceleration& Acceleration::operator+=(const Acceleration& other) {
    m_directional += other.directional();
    m_angular += other.angular();

    return *this;
}

Acceleration operator*(const Acceleration& other) const {
    return Acceleration(
         m_directional * other.directional(),
         m_angular * other.angular()
    );
}


