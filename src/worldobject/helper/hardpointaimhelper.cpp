#include "hardpointaimhelper.h"


#include "equipment/weapon.h"
#include "equipment/hardpoint.h"
#include "equipment/weapons/gun.h"

#include "physics/physics.h"

#include "utils/glmext/safenormalize.h"

#include "voxel/specialvoxels/hardpointvoxel.h"

#include "worldobject/worldobject.h"


HardpointAimHelper::HardpointAimHelper(Hardpoint* hardpoint, WorldObject* targetObject):
    m_hardpoint(hardpoint),
    m_targetObject(targetObject),
    m_bulletSpeed(0.0f),
    m_hitable(false),
    m_aimed(false),
    m_bulletLifetime(0.0f)
{
    assert(m_hardpoint->weapon());

    Gun& gun = dynamic_cast<Gun&>(*m_hardpoint->weapon().get());

    m_hardpointPosition = m_hardpoint->voxel()->position();

    m_targetPosition = m_targetObject->transform().position();
    m_targetSpeed = m_targetObject->physics().speed().directional();
    m_bulletSpeed = gun.bulletSpeed();
    m_bulletLifetime = Property<float>::get(gun.projectileName() + ".general.lifetime");
}

void HardpointAimHelper::aim() {
    float offset;
    int iterations = 0;

    m_point = m_targetPosition;

    do {
        float travelTime = bulletTravelTime(m_point);
        if(travelTime > m_bulletLifetime) {
            m_hitable = false;
            return;
        }

        offset = glm::length(targetPositionIn(travelTime) - m_point);
        m_point = targetPositionIn(travelTime);

        iterations++;
        if(iterations > 20) {
            m_hitable = false;
            return;
        }
    } while(offset > 0.1f);

    m_hitable = true;
    m_direction = safeNormalize(m_point - m_hardpointPosition);

    m_aimed = true;
}

bool HardpointAimHelper::isHittable() {
    if(!m_aimed) {
        aim();
    }
    return m_hitable;
}

const glm::vec3& HardpointAimHelper::direction() {
    if(!m_aimed) {
        aim();
    }
    return m_direction;
}

const glm::vec3& HardpointAimHelper::point() {
    if(!m_aimed) {
        aim();
    }
    return m_point;
}

float HardpointAimHelper::bulletTravelTime(const glm::vec3& point) {
    float distance = glm::length(point - m_hardpointPosition);
    return distance / m_bulletSpeed;
}

glm::vec3 HardpointAimHelper::targetPositionIn(float deltaSec) {
    return m_targetObject->transform().position() + m_targetObject->physics().speed().directional() * deltaSec;
}

