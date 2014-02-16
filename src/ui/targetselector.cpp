#include "ui/targetselector.h"

#include <algorithm>

#include "worldobject/ship.h"
#include "world/world.h"

#include "player.h"


TargetSelector::TargetSelector(Player *player):
    m_player(player)
{

}

void TargetSelector::selectTarget(bool next) {
    if (next) {
        m_player->setTarget(findNextTarget(World::instance()->worldObjects().begin(), World::instance()->worldObjects().end()));
    } else {
        m_player->setTarget(findNextTarget(World::instance()->worldObjects().rbegin(), World::instance()->worldObjects().rend()));
    }
}

template<typename IteratorType>
WorldObject* TargetSelector::findNextTarget(IteratorType begin, IteratorType end) {
    if (!m_player->playerShip()) {
        return nullptr;
    }

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

