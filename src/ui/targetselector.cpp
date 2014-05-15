#include "ui/targetselector.h"

#include <algorithm>

#include "worldobject/ship.h"
#include "worldobject/worldobjectinfo.h"

#include "world/world.h"

#include "player.h"


TargetSelector::TargetSelector(Player* player):
    m_player(player)
{

}

void TargetSelector::selectTarget(bool next) {
    if (next) {
        selectNextTarget();
    } else {
        selectPreviousTarget();
    }
}

void TargetSelector::selectNextTarget() {
    std::unordered_set<WorldObject*>& worldObjects = player->universe().worldObjects();
    m_player->setTarget(findNextTarget(worldObjects.begin(), worldObjects.end()));
}

void TargetSelector::selectPreviousTarget() {
    std::unordered_set<WorldObject*>& worldObjects = player->universe().worldObjects();
    // HACK: unordered sets don't have reverse iterators (on linux)
    // since this algorithm has to be improved anyway, for the moment previous will also go forward
    m_player->setTarget(findNextTarget(worldObjects.begin(), worldObjects.end()));
}

template<typename IteratorType>
WorldObject* TargetSelector::findNextTarget(IteratorType begin, IteratorType end) {
    if (!m_player->ship()) {
        return nullptr;
    }

    IteratorType searchBegin = begin;

    if (m_player->ship()->targetObject() != nullptr) {
        searchBegin = std::find(begin, end, m_player->ship()->targetObject());
        searchBegin++;
    }

    IteratorType newTarget = std::find_if(searchBegin, end, canLockOnPredicate());

    if(newTarget == end) {
        newTarget = std::find_if(begin, searchBegin, canLockOnPredicate());
        if(newTarget == searchBegin) {
            return nullptr;
        }
    }

    return newTarget != end ? *newTarget : nullptr;
}

std::function<bool(WorldObject*)> TargetSelector::canLockOnPredicate() {
    return [] (WorldObject* worldObject) {
        return worldObject->info().canLockOn();
    };
}

