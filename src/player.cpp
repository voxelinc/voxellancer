#include "player.h"

Player::Player(Camera* camera){
    m_camera = camera;
    m_shipOffset = glm::vec3(0, 5, 10);
}

void Player::accelerateShip(glm::vec3 direction){
    m_playerShip->accelerate(direction);
}

void Player::accelerateAngularShip(glm::vec3 direction){
    m_playerShip->accelerateAngular(direction);
}

void Player::setShip(Ship* ship){
    m_playerShip = ship;
    setFollowCam();
}

void Player::setFollowCam(){
    m_camera->setPosition(m_playerShip->transform().position());
    m_camera->move(glm::vec3(0, 5, 10));
    m_camera->setOrientation(m_playerShip->transform().orientation());
}

Ship* Player::playerShip(){
    return m_playerShip;
}

void Player::setShipToCam(){
    glm::vec3 newShipPosition = m_camera->position() - m_camera->orientation()*m_shipOffset;
    glm::vec3 diff = newShipPosition - m_playerShip->transform().position();
    m_playerShip->transform().setOrientation(glm::slerp(m_camera->orientation(), m_playerShip->transform().orientation(), 0.5f));
    //printf("+%f %f %f\n", m_camera->position().x, m_camera->position().y, m_camera->position().z);
    //printf("-%f %f %f\n", m_playerShip->transform().position().x, m_playerShip->transform().position().y, m_playerShip->transform().position().z);
    //printf("%f %f %f\n", diff.x, diff.y, diff.z);
    //printf("%f %f %f\n", newShipPosition.x, newShipPosition.y, newShipPosition.z);
    m_playerShip->accelerate(newShipPosition-m_playerShip->transform().position());
}