#pragma once

#include <glm/glm.hpp>


class Bullet;
class Hardpoint;

class BulletSpawnHelper {
public:
    BulletSpawnHelper(Bullet* bullet, Hardpoint* hardpoint, float bulletSpeed, const glm::vec3& target);

    void setupBullet();


protected:
    Bullet* m_bullet;
    Hardpoint* m_hardpoint;
    float m_bulletSpeed;
    glm::vec3 m_target;
};
