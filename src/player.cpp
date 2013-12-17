#include "player.h"

Player::Player(Camera* camera){
    m_camera = camera;
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
    setFollowCam();
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

void Player::setFollowCam(){
    m_camera->setPosition(m_playerShip->transform().position());
    m_camera->setOrientation(m_playerShip->transform().orientation());
    m_camera->move(glm::vec3(0, 5, 10));
}

Ship* Player::playerShip(){
    return m_playerShip;
}

void Player::setShipToCam(float delta_sec){
    acc *= 2;
    accAng /= 30;
    m_camera->move(acc);
    m_camera->rotateX(accAng.x);
    m_camera->rotateY(accAng.y);


    glm::vec3 newShipPosition = m_camera->position() - m_camera->orientation()*m_shipOffset;
    glm::vec3 diff = newShipPosition - m_playerShip->transform().position();
    glm::vec3 acc;

    //diff *= glm::length(diff)*glm::length(diff); //make alignement swifter
    diff *= 1;
    acc = diff - m_playerShip->physics().speed();
    m_playerShip->accelerateAngular(accAng);
    //acc /= 0.5;
    //printf("%f \n", glm::length(m_playerShip->physics().speed()));
    //m_playerShip->physics().setSpeed(newShipPosition - m_playerShip->transform().position());
    m_playerShip->accelerate(acc);
    //printf("+%f %f %f\n", m_camera->position().x, m_camera->position().y, m_camera->position().z);
    //printf("- %f %f %f\n", m_playerShip->physics().speed().x, m_playerShip->physics().speed().y, m_playerShip->physics().speed().z);
    //printf("+ %f %f %f\n", diff.x, diff.y, diff.z);
    //printf("%f %f %f\n", newShipPosition.x, newShipPosition.y, newShipPosition.z);
    //
    //simple alignement, no collision detection
    //m_playerShip->transform().setPosition(glm::mix(newShipPosition, m_playerShip->transform().position(), 0.9f));
    //m_playerShip->transform().setOrientation(glm::slerp(m_camera->orientation(), m_playerShip->transform().orientation(), 0.9f));

    acc = glm::vec3(0);
    accAng = glm::vec3(0);
}

void Player::boost(){

}