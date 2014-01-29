#include "bulletspawnhelper.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "geometry/transform.h"

#include "worldobject/hardpoint.h"
#include "worldobject/ship.h"
#include "utils/geometryhelper.h"

#include "bullet.h"


BulletSpawnHelper::BulletSpawnHelper(Bullet* bullet, Hardpoint* hardpoint, float bulletSpeed, const glm::vec3& target):
    m_bullet(bullet),
    m_hardpoint(hardpoint),
    m_bulletSpeed(bulletSpeed),
    m_target(target)
{

}

void BulletSpawnHelper::setupBullet() {
    Transform bulletTransform(m_bullet->transform());

    glm::quat shipOrientation = m_hardpoint->ship()->transform().orientation();
    glm::vec3 bulletDirection = glm::normalize(m_target - m_hardpoint->position());
    glm::vec3 hardpointDirection = shipOrientation * glm::vec3(0, 0, -1);
    glm::vec3 bulletUp = glm::cross(bulletDirection, hardpointDirection);

    //bulletTransform.setOrientation(Math::quatFromDir(bulletDirection));
    bulletTransform.setOrientation(m_hardpoint->ship()->transform().orientation());

    if (bulletUp != glm::vec3(0)) {
        glm::vec3 rotationAxis = glm::normalize(bulletUp);
        float angle = GeometryHelper::angleBetween(bulletDirection, hardpointDirection);
        glm::quat orientation = glm::angleAxis(-angle, rotationAxis);
        bulletTransform.rotateWorld(orientation); //then rotate towards target
    }

    
    //TODO: #300
    float bulletLength = m_bullet->minimalGridAABB().extent(ZAxis) * m_bullet->transform().scale();
    float spawnDistance = glm::root_two<float>() * m_bullet->transform().scale();
    bulletTransform.setPosition(m_hardpoint->position() + bulletDirection * (bulletLength / 2.0f + spawnDistance));

    m_bullet->setTransform(bulletTransform);
    m_bullet->physics().setSpeed(bulletDirection * m_bulletSpeed);
    m_bullet->physics().setAngularSpeed(glm::vec3(0.0f, 0.0f, 50.0f));
}


