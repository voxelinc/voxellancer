#include "player.h"

Player::Player() {
    m_shipOffset = glm::vec3(0, 5, 10);
    acc = glm::vec3(0);
    accAng = glm::vec3(0);
}

void Player::move(glm::vec3 direction){
    acc += direction;
    //m_camera->move(direction);
    //m_playerShip->accelerate(direction);
}

void Player::rotate(glm::vec3 direction){
    accAng += direction;
    //m_playerShip->accelerateAngular(direction);
}

void Player::setShip(Ship* ship){
    m_playerShip = ship;
}

void Player::applyAcceleration(){
    if (acc != glm::vec3(0))
        acc = glm::normalize(acc);
    m_playerShip->accelerate(acc);
    if (accAng == glm::vec3(0)){
        accAng = m_playerShip->physics().angularSpeed();
        accAng *= -1.5f;
    }
    m_playerShip->accelerateAngular(accAng);
    acc = glm::vec3(0);
    accAng = glm::vec3(0);
}

Ship* Player::playerShip() {
    return m_playerShip;
}
