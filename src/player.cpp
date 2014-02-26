#include "player.h"

#include "utils/aimer.h"
#include "utils/tostring.h"

#include "worldobject/ship.h"

#include "game.h"
#include "ui/hud/hud.h"
#include "ui/hud/hudget.h"
#include "ui/hud/aimhelperhudget.h"
#include "ui/hud/crosshair.h"
#include "physics/physics.h"
#include "camera/camerahead.h"
#include "camera/cameradolly.h"
#include "ui/objectinfo.h"
#include "worldobject/worldobjectcomponents.h"
#include "ui/targetselector.h"


Player::Player(Game* game):
    m_game(game),
    m_aimer(new Aimer(nullptr)),
    m_hud(new HUD(this, &game->viewer())),
    m_ship(nullptr),
    m_cameraDolly(new CameraDolly()),
    m_targetSelector(new TargetSelector(this))
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
    m_aimer->setWorldObject(ship);
}

void Player::update(float deltaSec) {
    m_cameraDolly->update(deltaSec);
    m_hud->update(deltaSec);
    m_aimer->update(deltaSec);

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
            targetPoint = m_aimer->aim(ray);
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

void Player::selectTarget(bool next) {
    m_targetSelector->selectTarget(next);
}

void Player::setTarget(WorldObject* target) {
    m_ship->setTargetObject(target);
    m_hud->setTarget(target);
}
