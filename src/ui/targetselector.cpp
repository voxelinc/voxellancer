#include "ui/targetselector.h"

#include <algorithm>


TargetSelector::TargetSelector(Player *player):
    m_player(player)
{

}

void TargetSelector::selectNextTarget() {
    std::list<WorldObject*>& worldObjects = World::instance()->worldObjects();
    m_player->playerShip()->setTargetObject(findNextTarget(worldObjects.begin(), worldObjects.end()));
}

void TargetSelector::selectPreviousTarget() {
    std::list<WorldObject*>& worldObjects = World::instance()->worldObjects();
    m_player->playerShip()->setTargetObject(findNextTarget(worldObjects.rbegin(), worldObjects.rend()));
}

template<typename IteratorType>
WorldObject* TargetSelector::findNextTarget(IteratorType begin, IteratorType end) {
    IteratorType searchBegin = begin;

    if (m_player->playerShip()->targetObject() != nullptr) {
        searchBegin = std::find(begin, end, m_player->playerShip()->targetObject());
        searchBegin++;
    }

    IteratorType newTarget = std::find_if(searchBegin, end, canLockOnPredicate());

    if(newTarget == end) {
        newTarget = std::find_if(begin, searchBegin, canLockOnPredicate());
    }

    return newTarget != end ? *newTarget : nullptr;
}

std::function<bool(WorldObject*)> TargetSelector::canLockOnPredicate() {
    return [] (WorldObject* worldObject) {
        return worldObject->objectInfo().canLockOn();
    };
}

