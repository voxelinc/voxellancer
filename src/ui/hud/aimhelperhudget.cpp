#include "aimhelperhudget.h"

#include <iostream>

#include "utils/geometryhelper.h"
#include "utils/tostring.h"

#include "worldobject/ship.h"
#include "worldobject/hardpoint.h"
#include "worldobject/helper/hardpointaimhelper.h"
#include "worldobject/weapons/weapon.h"

#include "player.h"

#include "hud.h"


AimHelperHudget::AimHelperHudget(HUD* hud):
    CircularHudget(hud, 4.0f),
    m_voxels(this),
    m_distanceRange(m_hud->sphere().radius() * 2, m_hud->sphere().radius() * 10)
{

}

const glm::vec3& AimHelperHudget::targetPoint() const {
    return m_targetPoint;
}

glm::vec3 AimHelperHudget::position() const {
    return m_position;
}

glm::quat AimHelperHudget::orientation() const {
    glm::vec3 direction = glm::inverse(m_hud->orientation()) * (position() - m_hud->centerOfView());
    glm::quat orientationOffset = GeometryHelper::quatFromViewDirection(direction);

    return m_hud->orientation() * orientationOffset;
}

void AimHelperHudget::update(float deltaSec) {
    Ship* ship = m_hud->player()->playerShip();
    WorldObject* targetObject = ship->targetObject();

    if (targetObject) {
        calculateTargetPoint(targetObject);
        calculatePosition();
    } else {
        setVisible(false);
    }
}

void AimHelperHudget::draw() {
    m_voxels.draw();
}

void AimHelperHudget::calculateTargetPoint(WorldObject* targetObject) {
    int hitableHardpointCount = 0;
    Ship* ship = m_hud->player()->playerShip();

    m_targetPoint = glm::vec3(0.0f, 0.0f, 0.0f);

    for(Hardpoint* hardpoint : ship->hardpoints()) {
        HardpointAimHelper aimHelper(hardpoint, targetObject);
        aimHelper.aim();

        if(aimHelper.isHitable()) {
            m_targetPoint += aimHelper.point();
            hitableHardpointCount++;
        }
    }

    if(hitableHardpointCount > 0) {
        setVisible(true);
        m_targetPoint /= hitableHardpointCount;
    } else {
        setVisible(false);
    }
}

void AimHelperHudget::calculatePosition() {
    glm::vec3 delta = m_targetPoint - m_hud->centerOfView();
    float distance = m_distanceRange.clamp(glm::length(delta));
    m_position = m_hud->centerOfView() + distance * glm::normalize(delta);
}

