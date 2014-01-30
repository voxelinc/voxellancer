#include "dummycharacter.h"

#include "ai/aitask.h"

DummyCharacter::DummyCharacter(Ship& ship, AiTask* task) :
    Character(ship),
    m_task(task)
{
}

void DummyCharacter::update(float deltaSec) {
    m_task->update(deltaSec);
}