#include "fight.h"

Fight::Fight(Ship& ship, std::list<std::shared_ptr<WorldObjectHandle>> targets) :
BasicTask(ship),
m_targets(targets)
{
    state = 0;
}

void Fight::update(float deltaSec) {
    updateTargets();

    if (m_targets.empty()) {
        return;
    }

    m_primaryTarget->objectInfo().setShowOnHud(true);
    m_primaryTarget->objectInfo().setCanLockOn(true);

    m_ship.boardComputer()->rotateTo(m_primaryTarget->transform().position());
    m_ship.boardComputer()->moveTo(m_primaryTarget->transform().position(), 30);
    m_ship.boardComputer()->shootBullet(m_targets);
}

void Fight::updateTargets() {
    auto iterator = m_targets.begin();
    while (iterator != m_targets.end()) {
        if (!(*iterator)->get()) {
            m_targets.erase(iterator++);
        } else {
            iterator++;
        }
    }

    if (!m_targets.empty()) {
        m_primaryTarget = m_targets.front()->get();
    }
}


void Fight::addTargets(std::list<std::shared_ptr<WorldObjectHandle>> targets) {
    m_targets.insert(m_targets.end(), targets.begin(), targets.end());
}

void Fight::setTargets(std::list<std::shared_ptr<WorldObjectHandle>> targets) {
    m_targets = targets;
}

bool Fight::isInProgress() {
    if (m_targets.empty()) {
        return true;
    }
    return false;
}

void Fight::updateState() {

}