#include "bullettransformhelper.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "geometry/transform.h"

#include "utils/math.h"

#include "worldobject/hardpoint.h"
#include "worldobject/ship.h"

#include "bullet.h"


BulletTransformHelper::BulletTransformHelper(Bullet* bullet, Hardpoint* hardpoint, float bulletSpeed, const glm::vec3& target):
    m_bullet(bullet),
    m_hardpoint(hardpoint),
    m_bulletSpeed(bulletSpeed),
    m_target(target)
{

}

void BulletTransformHelper::transform() {
    Transform bulletTransform(m_bullet->transform());

    glm::quat shipOrientation = m_hardpoint->ship()->transform().orientation();
    glm::vec3 bulletDirection = glm::normalize(m_target - m_hardpoint->position());
    glm::vec3 hardpointDirection = shipOrientation * glm::vec3(0, 0, -1);
    glm::vec3 bulletUp = glm::cross(bulletDirection, hardpointDirection);

    //bulletTransform.setOrientation(Math::quatFromDir(bulletDirection));
    bulletTransform.setOrientation(m_hardpoint->ship()->transform().orientation());

/*
    Below code leads to nan() - orientation of bullets sometimes.
    Please whoever wrote it, make it more readable and try to solve the bug
*/
    if (bulletUp != glm::vec3(0)) {
        glm::vec3 rotationAxis = glm::normalize(bulletUp);
        float angle = glm::acos(glm::dot(bulletDirection, hardpointDirection));
        bulletTransform.rotateWorld(glm::angleAxis(-glm::degrees(angle), rotationAxis)); //then rotate towards target
    }

    float bulletLength = m_bullet->minimalGridAABB().extent(ZAxis) * m_bullet->transform().scale();
    bulletTransform.setPosition(m_hardpoint->position() + bulletDirection * (bulletLength / 2.0f));

    m_bullet->setTransform(bulletTransform);
    m_bullet->physics().setSpeed(bulletDirection * m_bulletSpeed);
}


