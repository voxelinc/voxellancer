#include "player.h"

Player::Player(Camera* camera) {
    m_camera = camera;
    m_shipOffset = glm::vec3(0, 5, 10);
    acceleration = glm::vec3(0);
    accelerationAngular = glm::vec3(0);
}

void Player::move(glm::vec3 direction) {
    acceleration += direction;
}

void Player::rotate(glm::vec3 direction) {
    accelerationAngular += direction;
}

void Player::setShip(Ship* ship) {
    m_playerShip = ship;
    setFollowCam();
}

void Player::applyUpdate() {
    if (acceleration != glm::vec3(0)) {
        acceleration = glm::normalize(acceleration);
    }
    m_playerShip->accelerate(acceleration);
    if (accelerationAngular == glm::vec3(0)) { // dampen rotation
        accelerationAngular = m_playerShip->physics().angularSpeed();
        accelerationAngular *= -1.5f;
    }
    m_playerShip->accelerateAngular(accelerationAngular);
    acceleration = glm::vec3(0);
    accelerationAngular = glm::vec3(0);
}

void Player::setFollowCam() {
    m_camera->setPosition(glm::mix(m_camera->position(), m_playerShip->transform().position(), 0.5f));
    m_camera->setPosition(m_playerShip->transform().position());
    m_camera->setOrientation(glm::slerp(m_camera->orientation(), m_playerShip->transform().orientation(), 0.5f));
    m_camera->move(glm::vec3(0, m_playerShip->transform().center().y + 10, m_playerShip->transform().center().z + 15));
    m_camera->rotateX(-5);
}

Ship* Player::playerShip() {
    return m_playerShip;
}

void Player::setShipToCam(float delta_sec) {
    acceleration *= 2;
    accelerationAngular /= 30;
    m_camera->move(acceleration);
    m_camera->rotateX(accelerationAngular.x);
    m_camera->rotateY(accelerationAngular.y);


    glm::vec3 newShipPosition = m_camera->position() - m_camera->orientation()*m_shipOffset;
    glm::vec3 diff = newShipPosition - m_playerShip->transform().position();
    glm::vec3 acc;

    diff *= 1;
    acc = diff - m_playerShip->physics().speed();
    m_playerShip->accelerateAngular(accelerationAngular);
    m_playerShip->accelerate(acc);
    acc = glm::vec3(0);
    accelerationAngular = glm::vec3(0);
}

void Player::boost() {

}