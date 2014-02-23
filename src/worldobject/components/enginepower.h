#pragma once

#include <string>

#include <glm/glm.hpp>

#include "geometry/acceleration.h"

#include "enginestate.h"


/*
    Max acceleration per mass an engine - or mutiple engines accumulated -
    are able to perform.

    The glm::vec4 is coded like
    x = max accel in -x and +x direction
    y = max accel in -y and +y direction
    z = max accel in -z direction
    w = max accel in +z direction
*/
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


    static EnginePower fromProperties(const std::string& prefix);


protected:
    glm::vec4 m_directional;
    glm::vec3 m_angular;
};

