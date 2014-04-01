#include "aigrouptask.h"

#include "ai/squad.h"
#include "worldobject/ship.h"
#include "ai/character.h"
#include "ai/basictasks/formationmembertask.h"

AiGroupTask::AiGroupTask(Squad& squad) :
    m_squad(squad)
{
    if (m_squad.leader()) {
        onNewLeader(m_squad.leader());
    }
}

void AiGroupTask::update(float deltaSec) {

}

bool AiGroupTask::isInProgress() {
    return true;
}

void AiGroupTask::onMemberJoin(Ship* member) {
    // the member needs to get a task
}

void AiGroupTask::onMemberLeave(Ship* member) {
    // potentially remove from internal lists etc
}

void AiGroupTask::onNewLeader(Ship* leader) {
    // the new leader needs a new task set
    // discard state regarding old leader
}

void AiGroupTask::setLeaderTask(std::shared_ptr<AiTask> task) {
    assert(m_squad.leader());
    m_squad.leader()->character()->setTask(task);
}

void AiGroupTask::setMembersToFollowLeader() {
    for (Ship* member : m_squad.members()) {
        if (member != m_squad.leader()) {
            member->character()->setTask(std::make_shared<FormationMemberTask>(*member));
        }
    }
}