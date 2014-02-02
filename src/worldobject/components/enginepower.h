#pragma once

#include <glm/glm.hpp>

#include "geometry/acceleration.h"

#include "enginestate.h"


class EnginePower {
public:
    EnginePower();
    EnginePower(const glm::vec4& directional, const glm::vec3& angular);

    const glm::vec4& directional() const;
    void setDirectional(const glm::vec4& directional);

    const glm::vec3& angular() const;
    void setAngular(const glm::vec3& angular);

    Acceleration accelerationAt(const EngineState& engineState);

    EnginePower& operator+=(const EnginePower& other);


protected:
    glm::vec4 m_directional;
    glm::vec3 m_angular;
};

