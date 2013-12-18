#include "player.h"

Player::Player(Camera* camera) {
    m_camera = camera;
    m_shipOffset = glm::vec3(0, 5, 10);
    m_acceleration = glm::vec3(0);
    m_angularAcceleration = glm::vec3(0);
}

void Player::move(glm::vec3 direction) {
    m_acceleration += direction;
    //m_camera->move(direction);
    //m_playerShip->accelerate(direction);
}

void Player::rotate(glm::vec3 direction) {
    m_angularAcceleration += direction;
    //m_playerShip->accelerateAngular(direction);
}

void Player::setShip(Ship* ship) {
    m_playerShip = ship;
    setFollowCam();
}

void Player::applyAcceleration(){
    if (m_acceleration != glm::vec3(0)) {
        m_acceleration = glm::normalize(m_acceleration);
    }

    m_playerShip->accelerate(m_acceleration);

    if (m_angularAcceleration == glm::vec3(0)){
        m_angularAcceleration = m_playerShip->physics().angularSpeed();
        m_angularAcceleration *= -1.5f;
    }

    m_playerShip->accelerateAngular(m_angularAcceleration);
    m_acceleration = glm::vec3(0);
    m_angularAcceleration = glm::vec3(0);
}

void Player::setFollowCam(){
    m_camera->setPosition(m_playerShip->transform().position());
    m_camera->setOrientation(m_playerShip->transform().orientation());
    m_camera->move(glm::vec3(0, 5, 10));
}

Ship* Player::playerShip(){
    return m_playerShip;
}

void Player::setShipToCam(float delta_sec) {
    m_acceleration *= 2;
    m_angularAcceleration /= 30;
    m_camera->move(m_acceleration);
    m_camera->rotateX(m_angularAcceleration.x);
    m_camera->rotateY(m_angularAcceleration.y);


    glm::vec3 newShipPosition = m_camera->position() - m_camera->orientation()*m_shipOffset;
    glm::vec3 diff = newShipPosition - m_playerShip->transform().position();
    glm::vec3 m_acceleration;

    //diff *= glm::length(diff)*glm::length(diff); //make alignement swifter
    diff *= 1;
    m_acceleration = diff - m_playerShip->physics().speed();
    m_playerShip->accelerateAngular(m_angularAcceleration);
    //m_acceleration /= 0.5;
    //printf("%f \n", glm::length(m_playerShip->physics().speed()));
    //m_playerShip->physics().setSpeed(newShipPosition - m_playerShip->transform().position());
    m_playerShip->accelerate(m_acceleration);
    //printf("+%f %f %f\n", m_camera->position().x, m_camera->position().y, m_camera->position().z);
    //printf("- %f %f %f\n", m_playerShip->physics().speed().x, m_playerShip->physics().speed().y, m_playerShip->physics().speed().z);
    //printf("+ %f %f %f\n", diff.x, diff.y, diff.z);
    //printf("%f %f %f\n", newShipPosition.x, newShipPosition.y, newShipPosition.z);
    //
    //simple alignement, no collision detection
    //m_playerShip->transform().setPosition(glm::mix(newShipPosition, m_playerShip->transform().position(), 0.9f));
    //m_playerShip->transform().setOrientation(glm::slerp(m_camera->orientation(), m_playerShip->transform().orientation(), 0.9f));

    m_acceleration = glm::vec3(0);
    m_angularAcceleration = glm::vec3(0);
}

void Player::boost(){

}
