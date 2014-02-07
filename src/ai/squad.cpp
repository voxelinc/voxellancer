#include "squad.h"

#include "worldobject/ship.h"
#include "ai/character.h"

Squad::Squad(Ship* leader) :
    m_leader(leader),
    m_members()
{
}

Squad::~Squad() {
}

Ship* Squad::leader() {
    return m_leader;
}

void Squad::onMemberJoin(Ship* member) {
    assert(member);
    m_members.push_back(member);
}

void Squad::onMemberLeave(Ship* member) {
    std::vector<Ship*>::iterator it = std::find(m_members.begin(), m_members.end(), member);
    assert(it != m_members.end());
    m_members.erase(it);
}

void Squad::onLeaderDestroyed() {
    if (!m_members.empty()) {
        // choose new leader
        Ship* newleader = nullptr;
        float leadermass = 0;
        for (Ship* member : m_members) {
            float membermass = member->physics().mass();
            if (!newleader || membermass > leadermass) {
                newleader = member;
                leadermass = newleader->physics().mass();
            }
        }
        assert(newleader);
        m_leader = newleader;
    }
}

glm::vec3 Squad::formationPositionFor(Ship* member) {
    std::vector<Ship*>::iterator it = std::find(m_members.begin(), m_members.end(), member);
    assert(it != m_members.end());
    size_t position = it - m_members.begin();
    
    // this algorithm can be indefinitely complex. for now, build two "wings"
    if (position % 2 == 0) { //right wing
        float distance = m_leader->bounds().sphere().radius();
        for (int i = 0; i < position; i += 2) {
            distance += 2 * m_members[i]->bounds().sphere().radius() + 10;
        }
        distance += member->bounds().sphere().radius() + 10;
        return m_leader->transform().position() + m_leader->physics().speed() + m_leader->transform().orientation() * (distance * glm::normalize(glm::vec3(1, 0, 1)));
    } else { // left wing
        float distance = m_leader->bounds().sphere().radius();
        for (int i = 1; i < position; i += 2) {
            distance += 2 * m_members[i]->bounds().sphere().radius() + 10;
        }
        distance += member->bounds().sphere().radius() + 10;
        return m_leader->transform().position() + m_leader->physics().speed() + m_leader->transform().orientation() * (distance * glm::normalize(glm::vec3(-1, 0, 1)));
    }
}