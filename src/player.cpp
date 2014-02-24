#include "player.h"

#include "utils/aimer.h"
#include "utils/tostring.h"

#include "camera/cameradolly.h"

#include "worldobject/ship.h"


#include "camera/cameradolly.h"
#include "camera/camerahead.h"
#include "gamestate/game.h"
#include "gamestate/gameplay/gameplay.h"
#include "ui/hud/hud.h"
#include "ui/hud/hudget.h"
#include "ui/hud/aimhelperhudget.h"
#include "ui/hud/crosshair.h"
#include "ui/objectinfo.h"
#include "physics/physics.h"
#include "worldobject/worldobjectcomponents.h"


Player::Player(GamePlay* gamePlay):
    m_gamePlay(gamePlay),
    m_ship(nullptr),
    m_hud(new HUD(this, &m_gamePlay->game()->viewer())),
    m_cameraDolly(new CameraDolly())
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

CameraHead& Player::cameraHead() {
    return m_cameraDolly->cameraHead();
}

const CameraHead& Player::cameraHead() const {
    return m_cameraDolly->cameraHead();
}

HUD& Player::hud() {
    return *m_hud;
}

void Player::fire() {
    if(ship()) {
        glm::vec3 targetPoint;

        if(m_hud->aimHelper().hovered()) {
            targetPoint = m_hud->aimHelper().targetPoint();
        } else {
            glm::vec3 shootDirection(glm::normalize(m_hud->crossHair().worldPosition() - cameraHead().position()));
            Ray ray(m_hud->crossHair().worldPosition(), shootDirection);
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

