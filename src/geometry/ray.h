#pragma once

#include <glm/glm.hpp>


class Sphere;

class Ray {
public:
    Ray(const glm::vec3& origin, const glm::vec3& direction);

    const glm::vec3& origin() const;
    void setOrigin(const glm::vec3& origin);

    const glm::vec3& direction() const;
    void setDirection(const glm::vec3& direction);

    bool intersects(const Sphere& sphere) const;


protected:
    glm::vec3 m_origin;
    glm::vec3 m_direction;
};
