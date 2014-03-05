#include "player.h"

#include "ai/character.h"

#include "camera/cameradolly.h"
#include "camera/camerahead.h"

#include "factions/factionmatrix.h"
#include "factions/playerfaction.h"

#include "gamestate/game.h"
#include "gamestate/gameplay/gameplay.h"

#include "ui/hud/hud.h"
#include "ui/hud/hudget.h"
#include "ui/hud/aimhelperhudget.h"
#include "ui/hud/crosshair.h"
#include "ui/objectinfo.h"

#include "utils/aimer.h"

#include "physics/physics.h"

#include "utils/enemyselector.h"

#include "world/world.h"

#include "worldobject/ship.h"
#include "worldobject/worldobjectcomponents.h"


Player::Player(GamePlay* gamePlay):
    Character(nullptr, World::instance()->factionMatrix().playerFaction()),
    m_gamePlay(gamePlay),
    m_aimer(new Aimer(nullptr)),
    m_enemySelector(new EnemySelector(this)),
    m_hud(new HUD(this, &gamePlay->game()->viewer())),
    m_ship(nullptr),
    m_cameraDolly(new CameraDolly())
{

}

Player::~Player() = default;

Ship* Player::ship() {
    return m_ship.get();
}

void Player::setShip(Ship* ship) {
    m_ship = ship->shipHandle();

    m_ship->setCharacter(this);
    Character::setShip(m_ship.get());

    m_ship->objectInfo().setShowOnHud(false);
    m_cameraDolly->followWorldObject(ship);
    m_aimer->setWorldObject(ship);
}

void Player::selectNextEnemy() {
    if (!m_ship.get()) {
        return;
    }

    Ship* nextEnemy = m_enemySelector->nextEnemy();
    if(nextEnemy) {
        m_ship->setTargetObject(nextEnemy);
    }
}

void Player::update(float deltaSec) {
    m_cameraDolly->update(deltaSec);
    m_hud->update(deltaSec);
    m_aimer->update(deltaSec);
    m_enemySelector->update(deltaSec);

    if (Ship* ship = m_ship.get()) {
        ship->components().setEngineState(m_engineState);
    }
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

