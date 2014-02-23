#include "hardpointaimhelper.h"

#include <iostream>

#include "voxel/specialvoxels/hardpointvoxel.h"

#include "equipment/weapon.h"
#include "equipment/hardpoint.h"
#include "equipment/weapons/gun.h"
#include "worldobject/worldobject.h"
#include "physics/physics.h"


HardpointAimHelper::HardpointAimHelper(Hardpoint* hardpoint, WorldObject* targetObject):
    m_hardpoint(hardpoint),
    m_targetObject(targetObject),
    m_bulletSpeed(0.0f),
    m_hitable(false),
    m_aimed(false)
{
    assert(m_hardpoint->weapon());

    Gun& gun = dynamic_cast<Gun&>(*m_hardpoint->weapon().get());

    m_shooterPosition = m_hardpoint->voxel()->position();
    m_targetPosition = m_targetObject->transform().position();
    m_bulletSpeed = gun.bulletSpeed();
    m_targetSpeed = m_targetObject->physics().speed().directional();
}

void HardpointAimHelper::aim() {
    float offset;
    int iterations = 0;

    m_point = m_targetPosition;

    do {
        float timeDelta = bulletTravelTime(m_point);
        offset = glm::length(targetPositionIn(timeDelta) - m_point);
        m_point = targetPositionIn(timeDelta);

        iterations++;
        if(iterations > 20) {
            m_hitable = false;
            return;
        }
    } while(offset > 0.1f);

    m_hitable = true;
    m_direction = glm::normalize(m_point - m_shooterPosition);

    m_aimed = true;
}

bool HardpointAimHelper::isHitable() {
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
    float distance = glm::length(point - m_shooterPosition);
    return distance / m_bulletSpeed;
}

glm::vec3 HardpointAimHelper::targetPositionIn(float deltaSec) {
    return m_targetObject->transform().position() + m_targetObject->physics().speed().directional() * deltaSec;
}

