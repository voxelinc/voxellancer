#include "player.h"

#include "ui/hud.h"
#include "camera/cameradolly.h"
#include "worldobject/ship.h"


Player::Player():
    m_hud(this),
    m_cameraDolly(),
    m_ship(nullptr)
{

}

Ship* Player::ship() {
    return m_ship.get();
}

void Player::setShip(Ship* ship) {
    m_ship = ship->shipHandle();
    m_ship->objectInfo().setShowOnHud(false);
    m_cameraDolly.followWorldObject(ship);
}

void Player::update(float deltaSec) {
    m_cameraDolly.update(deltaSec);
    m_hud.update(deltaSec);

    if (Ship* ship = m_ship.get()) {
        ship->components().setEngineState(m_engineState);
    }

    m_engineState.clear();
}

CameraDolly& Player::cameraDolly() {
    return m_cameraDolly;
}

HUD& Player::hud() {
    return m_hud;
}

void Player::move(const glm::vec3& vec) {
    m_engineState.setDirectional(vec);
}

void Player::rotate(const glm::vec3& euler) {
    m_engineState.setAngular(euler);
}
