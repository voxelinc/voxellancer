#include "player.h"

#include "ai/character.h"
#include "ai/playerboardcomputer.h"
#include "ai/squadlogic.h"

#include "camera/cameradolly.h"
#include "camera/camerahead.h"

#include "factions/factionmatrix.h"
#include "factions/faction.h"

#include "gamestate/game.h"
#include "gamestate/gameplay/gameplay.h"

#include "ui/hud/hud.h"
#include "ui/hud/hudget.h"
#include "ui/hud/crosshair.h"
#include "ui/targetselector.h"

#include "worldobject/worldobjectinfo.h"

#include "world/world.h"

#include "worldobject/ship.h"
#include "worldobject/worldobjectcomponents.h"



Player::Player() :
    Character(),
    m_hud(new HUD(this)),
    m_cameraDolly(new CameraDolly()),
    m_targetSelector(new TargetSelector(this))
{

}

Player::~Player() = default;

void Player::setShip(Ship* ship) {
    Character::setShip(ship);
    setFaction(World::instance()->factionMatrix().playerFaction());
    m_boardComputer = new PlayerBoardComputer(ship, m_hud.get(),m_targetSelector.get());
    ship->setBoardComputer(m_boardComputer);
    m_ship->info().setShowOnHud(false);
    m_cameraDolly->followWorldObject(ship);
}

void Player::update(float deltaSec) {
    Character::update(deltaSec);
    m_cameraDolly->update(deltaSec);
    m_hud->update(deltaSec);
}

CameraHead& Player::cameraHead() {
    return m_cameraDolly->cameraHead();
}

HUD& Player::hud() {
    return *m_hud;
}

void Player::fire() {
    if (ship()) {
        m_boardComputer->fire(glm::normalize(m_hud->crossHair().worldPosition() - cameraHead().position()));
    }
}

void Player::fireRocket() {
    if (ship()) {
        m_boardComputer->fireRocket();
    }
}

void Player::move(const glm::vec3& vec) {
    if (ship() && glm::length(vec) > 0) {
        m_boardComputer->move(vec);
    }
}

void Player::rotate(const glm::vec3& euler) {
    if (ship() && glm::length(euler) > 0) {
        m_boardComputer->rotate(euler);
    }
}

void Player::selectTarget(bool next) {
    m_targetSelector->selectTarget(next);
}

void Player::setTarget(WorldObject* target) {
    m_ship->setTargetObject(target);
    m_hud->setTarget(target);
}

void Player::joinSelectedSquad() {
    Ship* targetShip = dynamic_cast<Ship*>(m_ship->targetObject());
    if (targetShip && targetShip->squadLogic()->squad()) {
        m_ship->squadLogic()->joinSquadOf(targetShip);
    }
}
