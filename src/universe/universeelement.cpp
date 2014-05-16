#include "universeelement.h"


UniverseElement::UniverseElement():
    m_universe(nullptr),
    m_sector(nullptr)
    m_removalScheduled(false)
{
}

UniverseElement::~UniverseElement() = default;

Universe* UniverseElement::universe() {
    return m_universe;
}

Sector* UniverseElement::sector() {
    return m_sector;
}

bool UniverseElement::removalScheduled() const {
    return m_removalScheduled
}

void UniverseElement::scheduleRemoval() {
    m_removalScheduled = true;
}

void UniverseElement::update(float deltaSecs) {

}

void UniverseElement::spawn(Universe* universe) {
    doSpawn(universe, nullptr);
}

void UniverseElement::spawn(Sector* sector) {
    doSpawn(sector->universe(), sector);
}

