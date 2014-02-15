#pragma once

#include "ai/character.h"


class Ship;
class AiTask;

class DummyCharacter : public Character {
public:
    DummyCharacter(Ship& ship, AiTask* task);
    
    virtual void update(float deltaSec);

protected:
    AiTask* m_task;

};

