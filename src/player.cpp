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
    m_hud(new HUD(this)),
    m_character(makeHandle(new Character())),
    m_cameraDolly(new CameraDolly()),
    m_targetSelector(new TargetSelector(this))
{
}

Player::~Player() = default;

void Player::setShip(Ship* ship) {
    m_ship = makeHandle(ship);
    m_character = makeHandle(new Character());
    m_character->setShip(ship);
    m_character->setFaction(World::instance()->factionMatrix().playerFaction());
    m_boardComputer = new PlayerBoardComputer(ship, m_hud.get(),m_targetSelector.get());
    ship->setBoardComputer(m_boardComputer);
    ship->info().setShowOnHud(false);
    m_cameraDolly->followWorldObject(ship);
}

void Player::update(float deltaSec) {
    if (m_character.valid()) {
        m_character->update(deltaSec);
    }
    m_cameraDolly->update(deltaSec);
    m_hud->update(deltaSec);
}

CameraHead& Player::cameraHead() {
    return m_cameraDolly->cameraHead();
}

HUD& Player::hud() {
    return *m_hud;
}

void Player::selectTarget(bool next) {
    m_targetSelector->selectTarget(next);
}

void Player::setTarget(WorldObject* target) {
    m_ship->setTargetObject(target);
    m_hud->setTarget(target);
}

void Player::joinSelectedSquad() {
    if (m_ship->squadLogic()->squad()) {
        m_ship->squadLogic()->leaveSquad();
    }
    Ship* targetShip = dynamic_cast<Ship*>(m_ship->targetObject());
    if (targetShip && targetShip->squadLogic()->squad()) {
        m_ship->squadLogic()->joinSquadOf(targetShip);
    }
}

PlayerBoardComputer& Player::playerBoardComputer() {
    return *m_boardComputer;
}

bool Player::hasShip() {
    return m_ship.valid();
}

Ship* Player::ship() {
    return m_ship.get();
}

void Player::leaveSquad() {
    if (m_ship->squadLogic()->squad()) {
        m_ship->squadLogic()->leaveSquad();
    }
}