#pragma once

#include <vector>
#include <memory>

#include "glm/glm.hpp"


class Ship;
class AiGroupTask;

class Squad {
public:
    Squad(Ship* leader = nullptr);
    ~Squad();

    Ship* leader();
    void setLeader(Ship* leader);

    std::shared_ptr<AiGroupTask> task();
    void setTask(std::shared_ptr<AiGroupTask> task);

    const std::vector<Ship*>& members();


protected:
    friend class SquadLogic;

    // Interface for SquadLogic
    void onMemberJoin(Ship* member);
    void onMemberLeave(Ship* member);
    glm::vec3 formationPositionFor(Ship* member);
    glm::vec3 formationUpFor(Ship* member);


    void chooseNewLeader();
    glm::vec3 calculateFormationPosition(Ship* member, int position);

    Ship* m_leader;
    std::vector<Ship*> m_members;
    std::shared_ptr<AiGroupTask> m_task;
};

