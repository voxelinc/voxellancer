#include "player.h"

#include "ui/hud.h"
#include "camera/cameradolly.h"
#include "worldobject/ship.h"


Player::Player():
    m_hud(new HUD(this)),
    m_cameraDolly(new CameraDolly()),
    m_playerShip(nullptr)
{

}

Player::~Player() = default;

void Player::move(const glm::vec3& direction) {
    m_acceleration += direction;
}

void Player::rotate(const glm::vec3& direction) {
    m_accelerationAngular += direction;
}

void Player::setShip(Ship* ship) {
    m_playerShip = ship->shipHandle();
    m_cameraDolly->followWorldObject(ship);
}

void Player::update(float deltaSec) {
    m_cameraDolly->update(deltaSec);
    m_hud->update(deltaSec);

    if (Ship* playerShip = m_playerShip.get()) {
        if (m_acceleration != glm::vec3(0)) {
            m_acceleration = glm::normalize(m_acceleration);
        }
        playerShip->accelerate(m_acceleration);

        if (m_accelerationAngular == glm::vec3(0)) { // dampen rotation
            m_accelerationAngular = playerShip->physics().angularSpeed();
            m_accelerationAngular *= -1.5f;
        }
        playerShip->accelerateAngular(m_accelerationAngular);
    }
    m_acceleration = glm::vec3(0);
    m_accelerationAngular = glm::vec3(0);
}

Ship* Player::playerShip() {
    return m_playerShip.get();
}

CameraDolly& Player::cameraDolly() {
    return *m_cameraDolly;
}

HUD& Player::hud() {
    return *m_hud;
}

glm::vec3 Player::cameraPosition() {
    return m_cameraDolly->cameraHead().position();
}

glm::quat Player::cameraOrientation() {
    return m_cameraDolly->cameraHead().orientation();
}



