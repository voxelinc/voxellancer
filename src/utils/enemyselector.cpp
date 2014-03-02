#include "enemyselector.h"

#include "ai/character.h"

#include "worldobject/ship.h"

#include "worldtree/worldtreescanner.h"


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

Character* EnemySelector::nearestEnemy() {
    return nullptr;
}

void EnemySelector::update(float deltaSec) {
    Ship& ship = m_character->ship();
    m_scanner->update(deltaSec, &ship);
}

