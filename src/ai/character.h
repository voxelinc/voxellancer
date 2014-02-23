#pragma once

#include <memory>

class Ship;
class AiTask;

class Character {
public:
    Character(Ship& ship);
    Character(Ship& ship, int faction);

    void setTask(std::shared_ptr<AiTask> task);
    std::shared_ptr<AiTask> task();
    
    virtual void update(float deltaSec);

    int faction();
    void setFaction(int faction);

protected:
    Ship& m_ship;
    std::shared_ptr<AiTask> m_task;

    // placeholder until faction system is implemented
    int m_faction;
};

