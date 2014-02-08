#pragma once

#include <vector>

#include "glm/glm.hpp"


class Ship;

class FormationLogic {
public:
    FormationLogic(Ship& ship);
    ~FormationLogic();
    Ship* ship();

    void joinFormation(Ship* leader);
    void joinFormation(FormationLogic* leader);
    void leaveFormation();

    glm::vec3 formationPosition();
    glm::vec3 formationUp();
    bool inFormation();

    void onDestruction();


protected:
    void onMemberJoin(FormationLogic* member);
    void onMemberLeave(FormationLogic* member);
    glm::vec3 formationPositionFor(FormationLogic* member);
    glm::vec3 calculateFormationPosition(FormationLogic* member, size_t position, bool rightWing);

    Ship& m_ship;
    FormationLogic* m_leader;
    std::vector<FormationLogic*> m_members;
};

