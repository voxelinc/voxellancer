#include "enemyselector.h"

#include "ai/character.h"

#include "collision/collisionfilter.h"

#include "factions/faction.h"
#include "factions/factionrelation.h"

#include "ui/objectinfo.h"

#include "worldobject/ship.h"

#include "worldobject/ship.h"

#include "worldtree/worldtreescanner.h"


namespace {
class EnemyFilter : public CollisionFilter {
public:
    EnemyFilter(Faction* faction, WorldObject* owner):
        CollisionFilter(owner, 0x00000000),
        m_faction(faction)
    {
        setCollideableWith(WorldObjectType::Ship, true);
    }


    bool specialIsCollideableWith(const CollisionFilter* other) const {
        WorldObject* worldObject = other->owner();

        if (worldObject) {
            if (worldObject->objectType() == WorldObjectType::Ship) {
                Ship* otherShip = static_cast<Ship*>(worldObject);
                Character* otherCharacter = otherShip->character();

                if (otherCharacter) {
                    Faction* otherFaction = otherCharacter->faction();

                    if (otherFaction) {
                        return m_faction->relationTo(otherFaction)->type() == FactionRelationType::Enemy;
                    }
                }
            }
        }
        return false;
    }

protected:
    Faction* m_faction;
};
}

EnemySelector::EnemySelector(Character* character):
    m_character(character),
    m_scanner(new WorldTreeScanner())
{
    m_scanner->setScanRadius(250);
    m_scanner->setScanInterval(0.2f);
}

EnemySelector::~EnemySelector() = default;

float EnemySelector::scanRadius() const {
    return m_scanner->scanRadius();
}

void EnemySelector::setScanRadius(float scanRadius) {
    m_scanner->setScanRadius(scanRadius);
}

Ship* EnemySelector::nextEnemy() {
    Ship* ship = m_character->ship();

    if (ship) {
        WorldObject* currentEnemy = ship->targetObject();
        WorldObject* nextEnemy = findNextEnemy(m_scanner->worldObjects().begin(), m_scanner->worldObjects().end(), currentEnemy);

        if (nextEnemy) {
            assert(nextEnemy->objectType() == WorldObjectType::Ship);
            return static_cast<Ship*>(nextEnemy);
        }
    }

    return nullptr;
}

void EnemySelector::update(float deltaSec) {
    Faction* faction = m_character->faction();
    if (!faction) {
        return;
    }

    Ship* ship = m_character->ship();

    if (ship) {
        m_scanner->setFilter(new EnemyFilter(faction, ship));
        m_scanner->update(deltaSec, ship);
    }
}



template<typename IteratorType>
WorldObject* EnemySelector::findNextEnemy(IteratorType begin, IteratorType end, WorldObject* currentEnemy) {
    IteratorType searchBegin = begin;

    if (currentEnemy != nullptr) {
        searchBegin = std::find(begin, end, currentEnemy);
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

std::function<bool(WorldObject*)> EnemySelector::canLockOnPredicate() {
    return [] (WorldObject* worldObject) {
        return worldObject->objectInfo().canLockOn();
    };
}
