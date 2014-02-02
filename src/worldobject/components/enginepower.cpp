#include "enginepower.h"


EnginePower::EnginePower():
    EnginePower(glm::vec4(0.0f), glm::vec3(0.0f))
{
}

EnginePower::EnginePower(const glm::vec4& directional, const glm::vec3& angular):
    m_directional(directional),
    m_angular(angular)
{
}

const glm::vec4& EnginePower::directional() const {
    return m_directional;
}

void EnginePower::setDirectional(const glm::vec4& directional) {
    m_directional = directional;
}

const glm::vec3& EnginePower::angular() const {
    return m_angular;
}

void EnginePower::setAngular(const glm::vec3& angular) {
    m_angular = angular;
}

Acceleration EnginePower::accelerationAt(const EngineState& engineState) {
    return Acceleration(
        glm::vec3(m_directional.x, m_directional.y, engineState.directional().z < 0 ? m_directional.z : m_directional.w) * engineState.directional(),
        m_angular * engineState.angular()
    );
}

EnginePower& EnginePower::operator+=(const EnginePower& other) {
    m_directional += other.directional();
    m_angular += other.angular();
    return *this;
}
