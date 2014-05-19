#include "ship.h"

#include "ai/boardcomputer.h"
#include "ai/character.h"
#include "ai/squadlogic.h"

#include "player.h"

#include "factions/factionmatrix.h"

#include "worldobject/worldobjectinfo.h"

#include "world/world.h"


Ship::Ship():
    WorldObject(),
    m_character(new Character(*this, World::instance()->factionMatrix().unknownFaction())),
    m_boardComputer(new BoardComputer(this)),
    m_squadLogic(new SquadLogic(*this)),
    m_shipHandle(Handle<Ship>(this)),
    m_targetObjectHandle(Handle<WorldObject>(nullptr))
{
    m_info->setShowOnHud(true);
    m_info->setCanLockOn(true);
}

Ship::~Ship() {
    m_shipHandle.invalidate();
}

WorldObjectType Ship::objectType() const {
    return WorldObjectType::Ship;
}

void Ship::update(float deltaSec) {
    WorldObject::update(deltaSec);

    m_character->update(deltaSec);
    m_boardComputer->update(deltaSec);
}

Handle<Ship>& Ship::handle() {
    return m_shipHandle;
}

void Ship::setTargetObject(WorldObject* target) {
    m_targetObjectHandle = target ? target->handle() : Handle<WorldObject>(nullptr);
}

WorldObject* Ship::targetObject() {
    return m_targetObjectHandle.get();
}

void Ship::setCharacter(Character* character) {
    m_character.reset(character);
}

Character* Ship::character() {
    return m_character.get();
}

Character* Ship::character() const {
    return m_character.get();
}

BoardComputer* Ship::boardComputer() {
    return m_boardComputer.get();
}

SquadLogic* Ship::squadLogic() {
    return m_squadLogic.get();
}

void Ship::onCollisionWith(WorldObject* worldObject) {
    WorldObject::onCollisionWith(worldObject);
    m_character->onCollisionWith(worldObject);
}

void Ship::onDeath() {
    m_character->onKilledBy(m_lastDamager);
}

