#include "character.h"

#include "ai/aigrouptask.h"
#include "ai/aitask.h"
#include "ai/squad.h"
#include "ai/squadlogic.h"

#include "worldobject/ship.h"

#include "world/world.h"

#include "factions/factionmatrix.h"


Character::Character(Ship* ship) :
    m_task(nullptr)
{
    m_faction = &World::instance()->factionMatrix().unknownFaction();
    m_ship = makeHandle(ship);
}

Character::Character() : 
    m_task(nullptr) 
{

}

Faction& Character::faction() {
    return *m_faction;
}

void Character::setFaction(Faction& faction) {
    m_faction = &faction;
}

void Character::setTask(std::shared_ptr<AiTask> task) {
    m_task = task;
}

std::shared_ptr<AiTask> Character::task() {
    return m_task;
}

void Character::update(float deltaSec) {
    if (m_ship->squadLogic()->isSquadLeader() && m_ship->squadLogic()->squad()->task().get()) {
        m_ship->squadLogic()->squad()->task()->update(deltaSec);
    }
    if (m_task.get()) {
        m_task->update(deltaSec);
    }
}

Ship* Character::ship() {
    return m_ship.get();
}

void Character::setShip(Ship* ship) {
    m_ship = makeHandle(ship);
    ship->setCharacter(this);
}
