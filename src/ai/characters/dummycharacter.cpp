#include "dummycharacter.h"

#include "ai/elevatedtask.h"

DummyCharacter::DummyCharacter(Ship& ship, ElevatedTask* task) :
    Character(ship),
    m_task(task)
{
}

void DummyCharacter::update(float deltaSec) {
    m_task->update(deltaSec);
}