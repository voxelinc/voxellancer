#pragma once

#include "ai/character.h"

class Ship;
class ElevatedTask;

class DummyCharacter : public Character {
public:
    DummyCharacter(Ship& ship, ElevatedTask* task);
    
    virtual void update(float deltaSec);

protected:
    ElevatedTask* m_task;

};

