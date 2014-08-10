#include "character.h"

#include "ai/aigrouptask.h"
#include "ai/aitask.h"
#include "ai/squad.h"
#include "ai/squadlogic.h"

#include "worldobject/ship.h"


Character::Character():
    m_name("Unnamed Character"),
    m_faction(nullptr)
{
}

Character::~Character() = default;

const std::string& Character::name() const {
    return m_name;
}

void Character::setName(const std::string& name) {
    m_name = name;
}

Faction* Character::faction() {
    return m_faction;
}

void Character::setFaction(Faction* faction) {
    m_faction = faction;
}

Ship* Character::ship() {
    return m_ship.get();
}

void Character::setShip(Ship* ship) {
    assert(ship->character().get() == this); // Relation has to be established by calling ship->setCharacter()

    Ship* oldShip = m_ship.get();
    m_ship = makeHandle(ship);

    onShipChanged(oldShip);
}

std::shared_ptr<AiTask>& Character::task() {
    return m_task;
}

void Character::setTask(std::shared_ptr<AiTask> task) {
    m_task = task; std::cout << "Setting task " << name() << " " << m_task << std::endl;
}

void Character::update(float deltaSec) {
    if (m_ship.valid()) {
        if (m_ship->squadLogic()->isSquadLeader() && m_ship->squadLogic()->squad()->task().get()) {
            m_ship->squadLogic()->squad()->task()->update(deltaSec);
        }
    }
}

void Character::onShipChanged(Ship* oldShip) {

}

