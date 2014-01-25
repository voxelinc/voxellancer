#pragma once

#include <glm/glm.hpp>


class Bullet;
class Hardpoint;

class BulletTransformHelper {
public:
    BulletTransformHelper(Bullet* bullet, Hardpoint* hardpoint, float bulletSpeed, const glm::vec3& target);

    void transform();


protected:
    Bullet* m_bullet;
    Hardpoint* m_hardpoint;
    float m_bulletSpeed;
    glm::vec3 m_target;
};
