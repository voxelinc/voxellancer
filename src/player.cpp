#include "player.h"

#include "utils/aimer.h"

#include "worldobject/ship.h"
#include "world/world.h"

#include "game.h"



Player::Player(Game* game):
    m_game(game),
    m_playerShip(nullptr),
    m_hud(this, &game->viewer())
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

HUD& Player::hud() {
    return m_hud;
}

glm::vec3 Player::cameraPosition() {
    return m_cameraDolly.cameraHead().position();
}

glm::quat Player::cameraOrientation() {
    return m_cameraDolly.cameraHead().orientation();
}

void Player::selectTarget(bool next) {
    if (next) {
        playerShip()->setTargetObject(findNextTarget(World::instance()->worldObjects().begin(), World::instance()->worldObjects().end()));
    } else {
        playerShip()->setTargetObject(findNextTarget(World::instance()->worldObjects().rbegin(), World::instance()->worldObjects().rend()));
    }
}

template<typename IteratorType>
WorldObject* Player::findNextTarget(IteratorType begin, IteratorType end) {
    if (!playerShip()) {
        return nullptr;
    }

    IteratorType searchBegin = begin;

    if (playerShip()->targetObject() != nullptr) {
        searchBegin = std::find(begin, end, playerShip()->targetObject());
        searchBegin++;
    }

    IteratorType newTarget = std::find_if(searchBegin, end, canLockOnPredicate());

    if (newTarget == end) {
        newTarget = std::find_if(begin, searchBegin, canLockOnPredicate());
    }

    return newTarget != end ? *newTarget : nullptr;
}

std::function<bool(WorldObject*)> Player::canLockOnPredicate() {
    return [](WorldObject* worldObject) {
        return worldObject->objectInfo().canLockOn();
    };
}

