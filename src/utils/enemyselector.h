#pragma once

#include <memory>
#include <functional>


class Character;
class Ship;
class WorldObject;
class WorldTreeScanner;

class EnemySelector {
public:
    EnemySelector(Character* character);
    ~EnemySelector();

    float scanRadius() const;
    void setScanRadius(float scanRadius);

    Ship* nextEnemy();

    void update(float deltaSec);


protected:
    Character* m_character;
    std::unique_ptr<WorldTreeScanner> m_scanner;


    template<typename IteratorType>
    WorldObject* findNextEnemy(IteratorType begin, IteratorType end, WorldObject* currentEnemy);

    std::function<bool(WorldObject*)> canLockOnPredicate();
};
