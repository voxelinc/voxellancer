#include "aimhelperhudget.h"

#include <iostream>

#include "utils/geometryhelper.h"
#include "utils/tostring.h"

#include "worldobject/ship.h"
#include "worldobject/components/hardpoint.h"
#include "worldobject/helper/hardpointaimhelper.h"
#include "worldobject/components/weapon.h"

#include "player.h"

#include "hud.h"


AimHelperHudget::AimHelperHudget(HUD* hud):
    CircularHudget(hud, 0.2f),
    m_voxels(this),
    m_distanceRange(m_hud->sphere().radius() * 2, m_hud->sphere().radius() * 10)
{

}

const glm::vec3& AimHelperHudget::targetPoint() const {
    return m_targetPoint;
}

void AimHelperHudget::update(float deltaSec) {
    Ship* ship = m_hud->player()->ship();

    if(!ship) {
        setVisible(false);
        return;
    }

    WorldObject* targetObject = ship->targetObject();

    if(!targetObject) {
        setVisible(false);
        return;
    }

    calculateTargetPoint(targetObject);

    pointToWorldPoint(m_targetPoint);
    setRelativeDistance(1.0f);

    if(hovered()) {
        setDirectionAngle(directionAngle() + 12.0f * deltaSec);
    } else {
        setDirectionAngle(0.0f);
    }
}

void AimHelperHudget::draw() {
    m_voxels.draw();
}

void AimHelperHudget::calculateTargetPoint(WorldObject* targetObject) {
    int hitableHardpointCount = 0;
    Ship* ship = m_hud->player()->ship();

    if(!ship) {
        return;
    }

    m_targetPoint = glm::vec3(0.0f, 0.0f, 0.0f);

    for(Hardpoint* hardpoint : ship->components().hardpoints()) {
        if(!hardpoint->weapon()) {
            continue;
        }
        if(hardpoint->weapon()->aimType() != WeaponAimType::Point) {
            continue;
        }

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

