#pragma once

#include <memory>

class Ship;
class AiTask;

class Character {
public:
    Character(Ship& ship);

    void setTask(std::shared_ptr<AiTask> task);
    std::shared_ptr<AiTask> task();
    
    virtual void update(float deltaSec);

protected:
    Ship& m_ship;
    std::shared_ptr<AiTask> m_task;

};

