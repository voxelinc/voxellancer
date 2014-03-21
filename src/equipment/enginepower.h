#pragma once

#include <string>

#include <glm/glm.hpp>

#include "geometry/acceleration.h"

#include "enginestate.h"


class Physics;

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

    /**
     *  maxmimum speed is at v * (1-dampening) = v + a
     *  a = -dampening * v
     */
    Acceleration accelerationAt(const EngineState& engineState, Physics& physics);

    EnginePower& operator+=(const EnginePower& other);


    static EnginePower fromProperties(const std::string& prefix);


protected:
    glm::vec4 m_directional;
    glm::vec3 m_angular;
};

