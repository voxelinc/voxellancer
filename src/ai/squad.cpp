#include "squad.h"

#include "worldobject/ship.h"
#include "ai/aigrouptask.h"
#include "utils/glmext/safenormalize.h"
#include "physics/physics.h"
#include "voxel/voxelclusterbounds.h"

Squad::Squad(Ship* leader) :
    m_leader(leader),
    m_task(nullptr),
    m_members()
{
}

Squad::~Squad() {
}

Ship* Squad::leader() {
    return m_leader;
}

void Squad::setLeader(Ship* leader) {
    assert(leader);
    if (m_leader) { // old leader becomes normal member
        onMemberJoin(m_leader);
    }
    std::vector<Ship*>::iterator it = std::find(m_members.begin(), m_members.end(), leader);
    if (it != m_members.end()) { // if leader was member, remove him
        m_members.erase(it);
        if (m_task)
            m_task->onMemberLeave(leader);
    }

    m_leader = leader;
    if (m_task) {
        m_task->onNewLeader(leader);
    }
}

std::shared_ptr<AiGroupTask> Squad::task() {
    return m_task;
}

void Squad::setTask(std::shared_ptr<AiGroupTask> task) {
    m_task = task;
}

const std::vector<Ship*>& Squad::members() {
    return m_members;
}

void Squad::onMemberJoin(Ship* member) {
    assert(member);
    if (!m_leader) { // auto-promote first member to leader
        m_leader = member;
        if (m_task) {
            m_task->onNewLeader(member);
        }
    } else {
        m_members.push_back(member);
        if (m_task) {
            m_task->onMemberJoin(member);
        }
    }
}

void Squad::onMemberLeave(Ship* member) {
    if (member == m_leader) {
        // the leader does not want to automatically become a member since he is about to leave
        m_leader = nullptr;
        chooseNewLeader();
    } else {
        std::vector<Ship*>::iterator it = std::find(m_members.begin(), m_members.end(), member);
        assert(it != m_members.end());
        m_members.erase(it);
        if (m_task) {
            m_task->onMemberLeave(member);
        }
    }
}

void Squad::chooseNewLeader() {
    if (!m_members.empty()) {
        Ship* newleader = nullptr;
        float leadermass = 0;
        // lacking another criteria, choose the heaviest guy
        for (Ship* member : m_members) {
            float membermass = member->physics().mass();
            if (!newleader || membermass > leadermass) {
                newleader = member;
                leadermass = newleader->physics().mass();
            }
        }
        assert(newleader);
        setLeader(newleader);
    } else {
        m_leader = nullptr;
    }
}

glm::vec3 Squad::formationPositionFor(Ship* member) {
    assert(m_leader); // no position without a leader
    std::vector<Ship*>::iterator it = std::find(m_members.begin(), m_members.end(), member);
    assert(it != m_members.end());
    size_t position = it - m_members.begin();

    return calculateFormationPosition(member, position);
}

glm::vec3 Squad::formationUpFor(Ship* member) {
    assert(m_leader); // no position without a leader
    return m_leader->transform().orientation() * glm::vec3(0, 1, 0);
}

glm::vec3 Squad::calculateFormationPosition(Ship* member, int position) {
    // this algorithm can be indefinitely complex. for now, build two "wings"
    float distance = m_leader->bounds().sphere().radius();
    for (int i = (position % 2); i < position; i += 2) {
        distance += 2 * m_members[i]->bounds().sphere().radius() + 10;
    }
    distance += member->bounds().sphere().radius() + 10;
    glm::vec3 direction = (position % 2) ? glm::vec3(1, 0, 1) : glm::vec3(-1, 0, 1);
    return m_leader->transform().position() + m_leader->physics().speed().directional() + m_leader->transform().orientation() * (distance * safeNormalize(direction));
}
