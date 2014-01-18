#include "player.h"

Player::Player(Camera* camera) {
    m_camera = camera;
    m_shipOffset = glm::vec3(0, 5, 10);
    m_acceleration = glm::vec3(0);
    m_accelerationAngular = glm::vec3(0);
}

void Player::move(glm::vec3 direction) {
    m_acceleration += direction;
}

void Player::rotate(glm::vec3 direction) {
    m_accelerationAngular += direction;
}

void Player::setShip(Ship* ship) {
    m_playerShip = ship;
    setFollowCam();
}

void Player::applyUpdate() {
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

void Player::setFollowCam() {
    m_camera->setPosition(glm::mix(m_camera->position(), m_playerShip->transform().position(), 0.5f));
    m_camera->setPosition(m_playerShip->transform().position());
    m_camera->setOrientation(glm::slerp(m_camera->orientation(), m_playerShip->transform().orientation(), 0.5f));
    m_camera->move(glm::vec3(0, m_playerShip->transform().center().y + 10, m_playerShip->transform().center().z + 15));
    //m_camera->rotateX(-5);
}

Ship* Player::playerShip() {
    return m_playerShip;
}

void Player::setShipToCam(float delta_sec) {
    m_acceleration *= 2;
    m_accelerationAngular /= 30;
    m_camera->move(m_acceleration);
    m_camera->rotateX(m_accelerationAngular.x);
    m_camera->rotateY(m_accelerationAngular.y);


    glm::vec3 newShipPosition = m_camera->position() - m_camera->orientation()*m_shipOffset;
    glm::vec3 diff = newShipPosition - m_playerShip->transform().position();
    glm::vec3 acc;

    diff *= 1;
    acc = diff - m_playerShip->physics().speed();
    m_playerShip->accelerateAngular(m_accelerationAngular);
    m_playerShip->accelerate(acc);
    acc = glm::vec3(0);
    m_accelerationAngular = glm::vec3(0);
}

void Player::boost() {

}