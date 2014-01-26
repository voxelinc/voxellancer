#include "hardpointaimhelper.h"

#include "worldobject/hardpoint.h"
#include "worldobject/worldobject.h"


HardpointAimHelper::HardpointAimHelper(Hardpoint* shooter, WorldObject* targetObject):
    m_shooter(shooter),
    m_targetObject(targetObject)
{
    assert(m_shooter->weapon());

    m_shooterPosition = m_shooter->position();
    m_targetPosition = m_targetObject->transform().position();
    m_bulletSpeed = m_shooter->weapon()->bulletSpeed();
    m_targetSpeed = m_targetObject->physics().speed();
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
        if(iterations > 10) {
            m_hitable = false;
            return;
        }
    } while(offset > 0.1f);

    m_hitable = true;

    m_direction = glm::normalize(m_point - m_shooterPosition);
}

bool HardpointAimHelper::isHitable() const {
    return m_hitable;
}

const glm::vec3& HardpointAimHelper::direction() const {
    return m_direction;
}

const glm::vec3& HardpointAimHelper::point() const {
    return m_point;
}

float HardpointAimHelper::bulletTravelTime(const glm::vec3& point) {
    float distance = glm::length(point - m_shooterPosition);
    return distance / m_bulletSpeed;
}

glm::vec3 HardpointAimHelper::targetPositionIn(float deltaSec) {
    return m_targetObject->transform().position() + m_targetObject->physics().speed() * deltaSec;
}

