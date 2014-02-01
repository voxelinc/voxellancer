#pragma once

#include <glm/glm.hpp>

/*
    Type for generic accelerations (absolute, relative, ...)
    directional-accel is stored in a vec4 of the following mapping (x, y, z-neg, z-pos)
    angular-accel is in euler angles
*/
class Acceleration {
public:
    Acceleration();
    Acceleration(const glm::vec4& directional, const glm::vec3& angular);

    /*
        Convenience constructor, if directional.z < 0 it will be stored in z, otherwise in w
    */
    Acceleration(const glm::vec3& directional, const glm::vec3& angular);

    void clear();

    const glm::vec4& directional() const;
    void setDirectional(const glm::vec4& directional);

    const glm::vec3& angular() const;
    void setAngular(const glm::vec3& angular);

    Acceleration& operator+=(const Acceleration& other);
    Acceleration operator*(const Acceleration& other) const;


protected:
    glm::vec4 m_directional;
    glm::vec3 m_angular;
};
