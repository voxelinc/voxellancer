#pragma once

#include <memory>


class Character;
class WorldTreeScanner;

class EnemySelector {
public:
    EnemySelector(Character* character);
    ~EnemySelector();

    float scanRadius() const;
    void setScanRadius(float scanRadius);

    Character* nearestEnemy();

    void update(float deltaSec);


protected:
    Character* m_character;
    std::unique_ptr<WorldTreeScanner> m_scanner;
};
