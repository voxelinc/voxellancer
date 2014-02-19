#include "player.h"

#include "utils/aimer.h"
#include "utils/tostring.h"

#include "camera/cameradolly.h"

#include "worldobject/ship.h"

#include "game.h"
#include "camera/cameradolly.h"
#include "ui/hud/hud.h"
#include "ui/hud/hudget.h"
#include "ui/hud/aimhelperhudget.h"
#include "ui/hud/crosshair.h"
#include "physics/physics.h"
#include "camera/camerahead.h"


Player::Player(Game* game):
    m_game(game),
    m_hud(this, &game->viewer()),
    m_ship(nullptr)
{
    
}

Player::~Player() = default;

Ship* Player::ship() {
    return m_ship.get();
}

void Player::setShip(Ship* ship) {
    m_ship = ship->shipHandle();
    m_ship->objectInfo().setShowOnHud(false);
    m_cameraDolly->followWorldObject(ship);
}

void Player::update(float deltaSec) {
    m_cameraDolly->update(deltaSec);
    m_hud->update(deltaSec);

    if (Ship* ship = m_ship.get()) {
        ship->components().setEngineState(m_engineState);
    }
}

CameraDolly& Player::cameraDolly() {
    return *m_cameraDolly;
}

HUD& Player::hud() {
    return *m_hud;
}

void Player::fire() {
    if(ship()) {
        glm::vec3 targetPoint;

        if(m_hud.aimHelper().hovered()) {
            targetPoint = m_hud.aimHelper().targetPoint();
        } else {
            glm::vec3 shootDirection(glm::normalize(m_hud.crossHair().worldPosition() - m_cameraDolly.cameraHead().position()));
            Ray ray(m_hud.crossHair().worldPosition(), shootDirection);
            targetPoint = Aimer(ship(), ray).aim();
        }

        ship()->components().fireAtPoint(targetPoint);
    }
}

void Player::move(const glm::vec3& vec) {
    m_engineState.setDirectional(vec);
}

void Player::rotate(const glm::vec3& euler) {
    m_engineState.setAngular(euler);
}

