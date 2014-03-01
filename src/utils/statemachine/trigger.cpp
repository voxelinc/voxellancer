#include "trigger.h"

#include "triggerable.h"


Trigger::Trigger(Triggerable* target):
    m_target(target)
{

}

Triggerable* Trigger::target() {
    return m_target;
}

void Trigger::setTarget(Triggerable* target) {
    m_target = target;
}

void Trigger::trigger() {
    if(m_target) {
        m_target->trigger();
    }
}

void Trigger::update(float deltaSec) {

}
