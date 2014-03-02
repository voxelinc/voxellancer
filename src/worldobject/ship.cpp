#include "ship.h"

#include "ai/boardcomputer.h"
#include "ai/character.h"
#include "ai/squadlogic.h"

#include "collision/collisionfilter.h"

#include "ui/objectinfo.h"


Ship::Ship():
    Ship(new CollisionFilter(this))
{
}

Ship::Ship(CollisionFilter* collisionFilter):
    WorldObject(collisionFilter),
    m_character(new Character(*this, nullptr)),
    m_boardComputer(new BoardComputer(this)),
    m_squadLogic(new SquadLogic(*this)),
    m_shipHandle(Handle<Ship>(this)),
    m_targetObjectHandle(Handle<WorldObject>(nullptr))
{
    m_objectInfo->setShowOnHud(true);
    m_objectInfo->setCanLockOn(true);
}

Ship::~Ship() {
    m_shipHandle.invalidate();
}

WorldObjectType Ship::objectType() const {
    return WorldObjectType::Ship;
}

ScriptableType Ship::scriptableType() const {
    return ScriptableType::Ship;
}

void Ship::update(float deltaSec) {
    WorldObject::update(deltaSec);

    m_character->update(deltaSec);
    m_boardComputer->update(deltaSec);
}

Handle<Ship> Ship::handle() {
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

BoardComputer* Ship::boardComputer() {
    return m_boardComputer.get();
}

SquadLogic* Ship::squadLogic() {
    return m_squadLogic.get();
}


