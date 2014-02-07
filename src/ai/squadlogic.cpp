#include "squadlogic.h"

#include "worldobject/ship.h"
#include "ai/character.h"

SquadLogic::SquadLogic(Ship& ship) :
    m_ship(ship),
    m_leader(nullptr),
    m_members()
{
}

SquadLogic::~SquadLogic() {
    onDestruction();
}

Ship* SquadLogic::ship() {
    return &m_ship;
}

void SquadLogic::joinFormation(Ship* leader) {
    assert(leader);
    joinFormation(leader->squadLogic());
}

void SquadLogic::joinFormation(SquadLogic* leader) {
    assert(m_leader == nullptr);
    assert(leader);
    assert(leader != this);
    m_leader = leader;
    m_leader->onMemberJoin(this);
}

void SquadLogic::leaveFormation() {
    assert(m_leader);
    m_leader->onMemberLeave(this);
    m_leader = nullptr;
}

glm::vec3 SquadLogic::formationPosition() {
    assert(m_leader);
    return m_leader->formationPositionFor(this);
}

glm::vec3 SquadLogic::formationUp() {
    assert(m_leader);
    return m_leader->ship()->transform().orientation() * glm::vec3(0, 1, 0);
}

bool SquadLogic::inFormation() {
    return m_leader != nullptr;
}

void SquadLogic::onDestruction() {
    if (inFormation()) {
        leaveFormation();
    }
    if (!m_members.empty()) {
        std::list<SquadLogic*> newmembers;

        // choose new leader
        SquadLogic* newleader = nullptr;
        float leadermass = 0;
        for (SquadLogic* member : m_members) {
            float membermass = member->ship()->physics().mass();
            if (!newleader || membermass > leadermass) {
                if (newleader) {
                    newmembers.push_back(newleader);
                }
                newleader = member;
                leadermass = newleader->ship()->physics().mass();
            } else {
                newmembers.push_back(member);
            }
        }
        
        // break up formation
        newleader->leaveFormation();
        for (SquadLogic* member : newmembers) {
            member->leaveFormation();
        }

        // assign everyone to new leader
        for (SquadLogic* member : newmembers) {
            if (member != newleader) {
                member->joinFormation(newleader);
            }
        }
    }
}

void SquadLogic::onMemberJoin(SquadLogic* member) {
    assert(m_leader == nullptr); // no stacking of formations
    m_members.push_back(member);
}

void SquadLogic::onMemberLeave(SquadLogic* member) {
    std::vector<SquadLogic*>::iterator it = std::find(m_members.begin(), m_members.end(), member);
    assert(it != m_members.end());
    m_members.erase(it);
}

glm::vec3 SquadLogic::formationPositionFor(SquadLogic* member) {
    std::vector<SquadLogic*>::iterator it = std::find(m_members.begin(), m_members.end(), member);
    assert(it != m_members.end());
    size_t position = it - m_members.begin();
    
    // this algorithm can be indefinitely complex. for now, build two "wings"
    if (position % 2 == 0) { //right wing
        float distance = m_ship.bounds().sphere().radius();
        for (int i = 0; i < position; i += 2) {
            distance += 2 * m_members[i]->ship()->bounds().sphere().radius() + 10;
        }
        distance += member->ship()->bounds().sphere().radius() + 10;
        return m_ship.transform().position() + m_ship.physics().speed() + m_ship.transform().orientation() * (distance * glm::normalize(glm::vec3(1, 0, 1)));
    } else { // left wing
        float distance = m_ship.bounds().sphere().radius();
        for (int i = 1; i < position; i += 2) {
            distance += 2 * m_members[i]->ship()->bounds().sphere().radius() + 10;
        }
        distance += member->ship()->bounds().sphere().radius() + 10;
        return m_ship.transform().position() + m_ship.physics().speed() + m_ship.transform().orientation() * (distance * glm::normalize(glm::vec3(-1, 0, 1)));
    }
}