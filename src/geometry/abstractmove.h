#pragma once

#include <glm/glm.hpp>

class AbstractMove {
public:
    AbstractMove();
    AbstractMove(const glm::vec3& directional, const glm::vec3& angular);

    void clear();

    const glm::vec3& directional() const;
    void setDirectional(const glm::vec3& directional);

    const glm::vec3& angular() const;
    void setAngular(const glm::vec3& angular);

    AbstractMove& operator+=(const AbstractMove& other);
    AbstractMove operator*(const AbstractMove& other) const;


protected:
    glm::vec3 m_directional;
    glm::vec3 m_angular;
};
