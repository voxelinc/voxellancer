#include "player.h"

#include "utils/aimer.h"

#include "worldobject/ship.h"

#include "gamestate/game.h"
#include "gamestate/gameplay/gameplay.h"


Player::Player(GamePlay* inGame):
    m_inGame(inGame),
    m_playerShip(nullptr),
    m_hud(this, &m_inGame->game()->viewer())
{

}

void Player::move(const glm::vec3& direction) {
    m_acceleration += direction;
}

void Player::rotate(const glm::vec3& direction) {
    m_accelerationAngular += direction;
}

void Player::fire() {
    if(playerShip()) {
        glm::vec3 targetPoint;

        if(m_hud.aimHelper().hovered()) {
            targetPoint = m_hud.aimHelper().targetPoint();
        } else {
            glm::vec3 shootDirection(glm::normalize(m_hud.crossHair().worldPosition() - m_cameraDolly.cameraHead().position()));
            Ray ray(m_hud.crossHair().worldPosition(), shootDirection);
            targetPoint = Aimer(playerShip(), ray).aim();
        }

        playerShip()->fireAtPoint(targetPoint);
    }
}

void Player::setShip(Ship* ship) {
    m_playerShip = ship->shipHandle();
    m_cameraDolly.followWorldObject(ship);
}

void Player::update(float deltaSec) {
    m_cameraDolly.update(deltaSec);
    m_hud.update(deltaSec);

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
    return m_cameraDolly;
}

const CameraDolly& Player::cameraDolly() const {
    return m_cameraDolly;
}

HUD& Player::hud() {
    return m_hud;
}

glm::vec3 Player::cameraPosition() {
    return m_cameraDolly.cameraHead().position();
}

glm::quat Player::cameraOrientation() {
    return m_cameraDolly.cameraHead().orientation();
}


