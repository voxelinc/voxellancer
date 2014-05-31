#include "playerboardcomputer.h"

#include "player.h"

#include "ui/hud/hud.h"
#include "ui/hud/aimhelperhudget.h"
#include "ui/hud/crosshair.h"

#include "worldobject/worldobject.h"
#include "worldobject/ship.h"
#include "worldobject/worldobjectcomponents.h"

#include "world/world.h"

#include "camera/camerahead.h"

#include "utils/aimer.h"

PlayerBoardComputer::PlayerBoardComputer(Ship* ship, HUD* hud, TargetSelector* targetSelector) :
BoardComputer(ship),
m_playerOrderPriority(OrderPriority::PLAYER),
m_hud(hud),
m_ship(ship),
m_targetSelector(targetSelector),
m_aimer(new Aimer(ship))
{    
}

void PlayerBoardComputer::fire(glm::vec3 from) {
    if (!isFireOrderAllowed(m_playerOrderPriority)) {
        return;
    } else {
        setFireOrderPriority(m_playerOrderPriority);
    }

    glm::vec3 targetPoint;

    if (m_hud->aimHelper().hovered()) {
        targetPoint = m_hud->aimHelper().targetPoint();
    } else {
        glm::vec3 shootDirection(glm::normalize(m_hud->crossHair().worldPosition() - from));
        Ray ray(m_hud->crossHair().worldPosition(), shootDirection);
        targetPoint = m_aimer->aim(ray);
    }

    m_worldObject->components().fireAtPoint(targetPoint, false);
}

void PlayerBoardComputer::fireRocket() {
    if (!isFireOrderAllowed(m_playerOrderPriority)) {
        return;
    } else {
        setFireOrderPriority(m_playerOrderPriority);
    }

    m_worldObject->components().fireAtObject(m_ship->targetObject());
}

void PlayerBoardComputer::move(const glm::vec3& vec) {
    if (glm::length(vec) == 0 || !isMoveOrderAllowed(m_playerOrderPriority)) {
        return;
    } else {
        setMoveOrderPriority(m_playerOrderPriority);
    }

    m_engineState.setDirectional(vec);
}

void PlayerBoardComputer::rotate(const glm::vec3& euler) {
    if (glm::length(euler) == 0 || !isMoveOrderAllowed(m_playerOrderPriority)) {
        return;
    } else {
        setMoveOrderPriority(m_playerOrderPriority);
    }

    m_engineState.setAngular(euler);
}

void PlayerBoardComputer::setShip(Ship* ship) {
    m_ship = ship;
    m_worldObject = ship;
    m_aimer->setWorldObject(ship);
}

void PlayerBoardComputer::update(float deltaSec) {
    m_aimer->update(deltaSec);
    BoardComputer::update(deltaSec);
}