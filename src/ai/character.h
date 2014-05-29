#pragma once

#include "utils/handle/handle.h"


class AiTask;
class Faction;
class Ship;

/**
 *  The Character is the Ship's pilot. He has a Faction which decides
 *  who is a friend or foe to him
 */
class Character {
public:
    Character();
    virtual ~Character();

    Faction* faction();
    void setFaction(Faction* faction);

    Ship* ship();
    void setShip(Ship *ship);

    std::shared_ptr<AiTask>& task();
    void setTask(std::shared_ptr<AiTask> task);

    virtual void update(float deltaSec);


protected:
    Handle<Ship> m_ship;
    Faction* m_faction;
    std::shared_ptr<AiTask> m_task;

    virtual void onShipChanged(Ship* oldShip);
};

