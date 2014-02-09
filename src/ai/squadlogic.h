#pragma once

#include <vector>

#include "glm/glm.hpp"


class Ship;

class SquadLogic
{
public:
    SquadLogic(Ship& ship);
    ~SquadLogic();
    Ship* ship();
    
    void joinFormation(Ship* leader);
    void joinFormation(SquadLogic* leader);
    void leaveFormation();

    glm::vec3 formationPosition();
    glm::vec3 formationUp();
    bool inFormation();

    void onDestruction();

protected:
    void onMemberJoin(SquadLogic* member);
    void onMemberLeave(SquadLogic* member);
    glm::vec3 formationPositionFor(SquadLogic* member);
    glm::vec3 calculateFormationPosition(SquadLogic* member, int position);

    Ship& m_ship;
    SquadLogic* m_leader;
    std::vector<SquadLogic*> m_members;
};

