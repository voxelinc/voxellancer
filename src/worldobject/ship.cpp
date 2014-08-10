#include "ship.h"

#include "ai/boardcomputer.h"
#include "ai/nonplayercharacter.h"
#include "ai/squadlogic.h"

#include "factions/factionmatrix.h"

#include "worldobject/worldobjectinfo.h"

#include "world/world.h"


Ship::Ship():
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

const std::shared_ptr<Character>& Ship::character() {
    return m_character;
}

void Ship::setCharacter(const std::shared_ptr<Character>& character) {
    if (m_character == character) {
        return;
    }

    if (m_character) {
        m_character->setShip(nullptr);
    }

    m_character = character;

    if (m_character) {
        m_character->setShip(this);
    }
}

BoardComputer* Ship::boardComputer() {
    return m_boardComputer.get();
}

SquadLogic* Ship::squadLogic() {
    return m_squadLogic.get();
}


