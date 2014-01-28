#include "player.h"

#include "ui/hud.h"
#include "camera/cameradolly.h"
#include "worldobject/ship.h"


Player::Player():
    m_hud(std::make_shared<HUD>(this)),
    m_cameraDolly(std::make_shared<CameraDolly>()),
    m_playerShip(nullptr)
{

}

void Player::move(const glm::vec3& direction) {
    m_acceleration += direction;
}

void Player::rotate(const glm::vec3& direction) {
    m_accelerationAngular += direction;
}

void Player::setShip(Ship* ship) {
    m_playerShip = ship;
    m_cameraDolly->followWorldObject(ship);
}

void Player::update(float deltaSec) {
    m_cameraDolly->update(deltaSec);
    m_hud->update(deltaSec);

    if (m_acceleration != glm::vec3(0)) {
        m_acceleration = glm::normalize(m_acceleration);
    }
    m_playerShip->accelerate(m_acceleration);

    if (m_accelerationAngular == glm::vec3(0)) { // dampen rotation
        m_accelerationAngular = m_playerShip->physics().angularSpeed();
        m_accelerationAngular *= -1.5f;
    }
    m_playerShip->accelerateAngular(m_accelerationAngular);

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

const glm::vec3& Player::cameraPosition() {
    return m_cameraDolly->cameraHead().position();
}

const glm::quat& Player::cameraOrientation() {
    return m_cameraDolly->cameraHead().orientation();
}


