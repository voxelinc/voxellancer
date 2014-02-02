#include "ui/targetselector.h"

#include <algorithm>

#include "player.h"
#include "worldobject/ship.h"
#include "world/world.h"
#include "worldtree/worldtreequery.h"
#include "worldtree/worldtree.h"
#include "collision/collisionfilterable.h"


namespace {
    class CollisionFilter : public CollisionFilterable {
    public:
        CollisionFilter(WorldObject* worldObject) :
            CollisionFilterable(CollisionFilterClass::Other),
            m_worldObject(worldObject) {
        }

        virtual bool specialIsCollideableWith(const CollisionFilterable *other) const override {
            return m_worldObject != other;
        }


    protected:
        WorldObject* m_worldObject;
    };
}

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

void TargetSelector::selectTargetOnClick() {
    /*if (!m_player->playerShip()) {
        return;
    }
    glm::vec3 shootDirection(glm::normalize(m_player->hud().crossHair().worldPosition() - m_player->cameraDolly().cameraHead().position()));
    Ray ray(m_player->hud().crossHair().worldPosition(), shootDirection);

    CollisionFilter collisionFilter(m_player->playerShip());
    collisionFilter.setCollideableWith(CollisionFilterClass::Other, false);
    WorldTreeQuery worldTreeQuery(&World::instance()->worldTree(), &ray, nullptr, &collisionFilter);
    std::set<WorldObject*> worldObjects = worldTreeQuery.intersectingWorldObjects();
    WorldObject* target = nullptr;
    
    for (std::set<WorldObject*>::iterator iterator; iterator != worldObjects.end(); iterator++) {
        if (!target) {
            target = *iterator;
        } else {
            if (glm::length(m_player->playerShip().transform().position()))
        }
        target = *iterator;

    }
    */
}

