#pragma once

#include <memory>


class AiTask;
class Faction;
class Ship;

class Character {
public:
    Character(Ship* ship, Faction* faction);

    Ship* ship();
    void setShip(Ship* ship);

    Faction* faction();
    void setFaction(Faction* faction);

    void setTask(std::shared_ptr<AiTask> task);
    std::shared_ptr<AiTask> task();

    virtual void update(float deltaSec);


protected:
    Ship* m_ship;
    Faction* m_faction;
    std::shared_ptr<AiTask> m_task;
};

