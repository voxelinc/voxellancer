#pragma once

#include "utils/handle/handle.h"

#include <memory>


class AiTask;
class Faction;
class Ship;

/**
 *  The Character is the Ship's pilot and executes his AiTask. He has a Faction which decides
 *  who is a friend or foe to him
 */
class Character {
public:
    Character(Ship* ship);
    Character();

    Faction& faction();
    void setFaction(Faction& faction);

    void setTask(std::shared_ptr<AiTask> task);
    std::shared_ptr<AiTask> task();

    virtual void update(float deltaSec);

    virtual void setShip(Ship* ship);
    Ship* ship();

protected:
    Handle<Ship> m_ship;
    Faction* m_faction;
    std::shared_ptr<AiTask> m_task;
};

