#pragma once

#include <memory>
#include <unordered_set>

#include <glm/glm.hpp>

#include "scripting/scriptable.h"

#include "utils/observer/observable.h"


class Ship;
class AiGroupTask;

/**
 *  Ships can be joined to Squads to give them AiGroupTasks. The Squad's leader is the one to execute the Squad's task.
 */
class Squad : public Scriptable, public Observable {
public:
    Squad(Ship* leader = nullptr);
    ~Squad();

    Ship* leader();
    void setLeader(Ship* leader);

    std::unordered_set<Ship*> members();
    std::unordered_set<Ship*> followers();

    void addMember(Ship* ship);
    void removeMember(Ship* ship);

    std::shared_ptr<AiGroupTask> task();
    void setTask(std::shared_ptr<AiGroupTask> task);

    glm::vec3 formationPositionFor(Ship* member);
    glm::vec3 formationUpFor(Ship* member);


protected:
    Ship* m_leader;
    std::unordered_set<Ship*> m_members;
    std::unordered_set<Ship*> m_followers;
    std::shared_ptr<AiGroupTask> m_task;

    void chooseNewLeader();
    glm::vec3 calculateFormationPosition(Ship* member, int position);
};

