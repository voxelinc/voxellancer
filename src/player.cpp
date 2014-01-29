#include "player.h"

#include "utils/aimer.h"

#include "game.h"


Player::Player(Game* game):
    m_game(game),
    m_hud(this, &game->viewer())
{

}

void Player::move(glm::vec3 direction) {
    m_acceleration += direction;
}

void Player::rotate(glm::vec3 direction) {
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
    m_playerShip = ship;
    m_cameraDolly.followWorldObject(ship);
}

void Player::update(float deltaSec) {
    m_cameraDolly.update(deltaSec);
    m_hud.update(deltaSec);

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
    return m_playerShip;
}

CameraDolly& Player::cameraDolly() {
    return m_cameraDolly;
}

HUD& Player::hud() {
    return m_hud;
}


