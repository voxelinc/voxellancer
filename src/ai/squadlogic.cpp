#include "squadlogic.h"

#include "worldobject/ship.h"
#include "ai/character.h"
#include "ai/squad.h"

SquadLogic::SquadLogic(Ship& ship) :
    m_ship(ship),
    m_squad(nullptr)
{
}

SquadLogic::~SquadLogic() {
    if (squad()) {
        leaveSquad();
    }
}

Ship* SquadLogic::ship() {
    return &m_ship;
}

void SquadLogic::joinSquadOf(Ship* member) {
    assert(member);
    assert(member->squadLogic()->squad()); // leader must be in a squad
    joinSquad(member->squadLogic()->squad());
}

void SquadLogic::joinSquad(std::shared_ptr<Squad> squad) {
    assert(m_squad.get() == nullptr);
    assert(squad.get());
    m_squad = squad;
    m_squad->onMemberJoin(&m_ship);
}

void SquadLogic::leaveSquad() {
    assert(m_squad.get());
    m_squad->onMemberLeave(&m_ship);
    m_squad = nullptr;
}

std::shared_ptr<Squad> SquadLogic::squad() {
    return m_squad;
}

bool SquadLogic::inSquad() {
    return m_squad.get() != nullptr;
}

bool SquadLogic::isSquadLeader() {
    return m_squad.get() && m_squad->leader() == &m_ship;
}

glm::vec3 SquadLogic::formationPosition() {
    assert(m_squad);
    return m_squad->formationPositionFor(&m_ship);
}

glm::vec3 SquadLogic::formationUp() {
    assert(m_squad);
    return m_squad->formationUpFor(&m_ship);
}