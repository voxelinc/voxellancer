#include "formationlogic.h"

#include "worldobject/ship.h"
#include "ai/character.h"

FormationLogic::FormationLogic(Ship& ship) :
    m_ship(ship),
    m_leader(nullptr),
    m_members()
{
}

FormationLogic::~FormationLogic() {
    onDestruction();
}

Ship* FormationLogic::ship() {
    return &m_ship;
}

void FormationLogic::joinFormation(Ship* leader) {
    assert(leader);
    joinFormation(leader->formationLogic());
}

void FormationLogic::joinFormation(FormationLogic* leader) {
    assert(m_leader == nullptr);
    assert(leader);
    assert(leader != this);
    m_leader = leader;
    m_leader->onMemberJoin(this);
}

void FormationLogic::leaveFormation() {
    assert(m_leader);
    m_leader->onMemberLeave(this);
    m_leader = nullptr;
}

glm::vec3 FormationLogic::formationPosition() {
    assert(m_leader);
    return m_leader->formationPositionFor(this);
}

glm::vec3 FormationLogic::formationUp() {
    assert(m_leader);
    return m_leader->ship()->orientation() * glm::vec3(0, 1, 0);
}

bool FormationLogic::inFormation() {
    return m_leader != nullptr;
}

void FormationLogic::onDestruction() {
    if (inFormation()) {
        leaveFormation();
    }
    if (!m_members.empty()) {
        std::list<FormationLogic*> newmembers;

        // choose new leader
        FormationLogic* newleader = nullptr;
        float leadermass = 0;
        for (FormationLogic* member : m_members) {
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
        for (FormationLogic* member : newmembers) {
            member->leaveFormation();
        }

        // assign everyone to new leader
        for (FormationLogic* member : newmembers) {
            if (member != newleader) {
                member->joinFormation(newleader);
            }
        }
    }
}

void FormationLogic::onMemberJoin(FormationLogic* member) {
    assert(m_leader == nullptr); // no stacking of formations
    m_members.push_back(member);
}

void FormationLogic::onMemberLeave(FormationLogic* member) {
    std::vector<FormationLogic*>::iterator it = std::find(m_members.begin(), m_members.end(), member);
    assert(it != m_members.end());
    m_members.erase(it);
}

glm::vec3 FormationLogic::formationPositionFor(FormationLogic* member) {
    std::vector<FormationLogic*>::iterator it = std::find(m_members.begin(), m_members.end(), member);
    assert(it != m_members.end());
    size_t position = it - m_members.begin();
    
    return calculateFormationPosition(member, position);
}

glm::vec3 FormationLogic::calculateFormationPosition(FormationLogic* member, int position) {
    float distance = m_ship.bounds().sphere().radius();
    for (int i = (position%2); i < position; i += 2) {
        distance += 2 * m_members[i]->ship()->bounds().sphere().radius() + 10;
    }
    distance += member->ship()->bounds().sphere().radius() + 10;
    glm::vec3 direction = position % 2 ? glm::vec3(1, 0, 1) : glm::vec3(-1, 0, 1);
    return m_ship.position() + m_ship.physics().speed() + m_ship.orientation() * (distance * glm::normalize(direction));
}