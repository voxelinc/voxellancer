#pragma once

#include <vector>

#include "glm/glm.hpp"


class Ship;

class Squad {
public:
    Squad(Ship* leader);
    ~Squad();
    Ship* leader();
    

protected:
    void onMemberJoin(Ship* member);
    void onMemberLeave(Ship* member);
    void onLeaderDestroyed();
    glm::vec3 formationPositionFor(Ship* member);

    Ship* m_leader;
    std::vector<Ship*> m_members;
};

