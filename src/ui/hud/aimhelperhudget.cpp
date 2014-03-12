#include "aimhelperhudget.h"

#include <glm/glm.hpp>

#include "utils/geometryhelper.h"
#include "utils/tostring.h"

#include "worldobject/ship.h"

#include "equipment/weapon.h"
#include "equipment/hardpoint.h"

#include "worldobject/worldobjectcomponents.h"
#include "worldobject/helper/hardpointaimhelper.h"

#include "player.h"

#include "hud.h"
#include "aimhelperhudgetvoxels.h"


AimHelperHudget::AimHelperHudget(HUD* hud):
    CircularHudget(hud, 0.25f),
    m_voxels(new AimHelperHudgetVoxels(this)),
    m_distanceRange(m_hud->sphere().radius() * 2, m_hud->sphere().radius() * 10),
    m_lastTargetWorldObject(nullptr),
    m_lastVisible(false)
{

}

AimHelperHudget::~AimHelperHudget() = default;

const glm::vec3& AimHelperHudget::targetPoint() const {
    return m_targetPoint;
}

void AimHelperHudget::update(float deltaSec) {
    Ship* ship = m_hud->player()->ship();

    if (!ship) {
        setVisible(false);
        return;
    }

    WorldObject* targetObject = ship->targetObject();

    if(!targetObject) {
        setVisible(false);
        return;
    }

    calculateTargetPoint(targetObject);

    if (m_lastTargetWorldObject == targetObject && m_lastVisible) {
        m_smoothTargetPoint = glm::mix(m_smoothTargetPoint, m_targetPoint, 5.0f * deltaSec);
    } else {
        m_smoothTargetPoint = m_targetPoint;
    }

    pointToWorldPoint(m_smoothTargetPoint);
    setRelativeDistance(1.0f);

    if (hovered()) {
        setDirectionAngle(directionAngle() + 12.0f * deltaSec);
    } else {
        setDirectionAngle(0.0f);
    }

    m_lastTargetWorldObject = targetObject;
    m_lastVisible = visible();
}

void AimHelperHudget::draw() {
    m_voxels->draw();
}

void AimHelperHudget::calculateTargetPoint(WorldObject* targetObject) {
    int hitableHardpointCount = 0;
    Ship* ship = m_hud->player()->ship();

    if (!ship) {
        return;
    }

    m_targetPoint = glm::vec3(0.0f, 0.0f, 0.0f);

    for (std::shared_ptr<Hardpoint> hardpoint : ship->components().hardpoints()) {
        if (!hardpoint->weapon()) {
            continue;
        }
        if (hardpoint->weapon()->type() != WeaponType::Gun) {
            continue;
        }

        HardpointAimHelper aimHelper(hardpoint.get(), targetObject);
        aimHelper.aim();

        if (aimHelper.isHitable()) {
            m_targetPoint += aimHelper.point();
            hitableHardpointCount++;
        }
    }

    if (hitableHardpointCount > 0) {
        setVisible(true);
        m_targetPoint /= hitableHardpointCount;
    } else {
        setVisible(false);
    }
}

