#pragma once

#include <vector>
#include <memory>

#include "glm/glm.hpp"
class Ship;
class Squad;

/**
 *  The SquadLogic is the single member's endpoint for interaction with a Squad
 */
class SquadLogic
{
public:
    SquadLogic(Ship& ship);
    ~SquadLogic();
    Ship* ship();

    void joinSquadOf(Ship* member);
    void joinSquad(std::shared_ptr<Squad> squad);
    void leaveSquad();
    std::shared_ptr<Squad> squad();
    bool inSquad();
    bool isSquadLeader();

    glm::vec3 formationPosition();
    glm::vec3 formationUp();


protected:
    Ship& m_ship;
    std::shared_ptr<Squad> m_squad;
};

