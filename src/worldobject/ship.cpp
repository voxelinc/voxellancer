#include "ship.h"

#include "ai/boardcomputer.h"
#include "ai/nonplayercharacter.h"
#include "ai/squadlogic.h"

#include "factions/factionmatrix.h"

#include "worldobject/worldobjectinfo.h"

#include "world/world.h"


Ship::Ship():
    WorldObject(),
    m_character(new NonPlayerCharacter()),
    m_boardComputer(new BoardComputer(this)),
    m_squadLogic(new SquadLogic(*this))
{
    m_character->setShip(this);

    m_info->setShowOnHud(true);
    m_info->setCanLockOn(true);
}

Ship::~Ship() = default;

WorldObjectType Ship::objectType() const {
    return WorldObjectType::Ship;
}

void Ship::update(float deltaSec) {
    WorldObject::update(deltaSec);

    m_character->update(deltaSec);
    m_boardComputer->update(deltaSec);
}

void Ship::setTargetObject(WorldObject* target) {
    m_targetObjectHandle = target ? makeHandle(target) : Handle<WorldObject>();
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

BoardComputer* Ship::boardComputer() {
    return m_boardComputer.get();
}

SquadLogic* Ship::squadLogic() {
    return m_squadLogic.get();
}


