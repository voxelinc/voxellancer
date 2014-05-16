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

void UniverseElement::setUniverse(Universe* universe) {
    m_universe = universe;
}

Sector* UniverseElement::sector() {
    return m_sector;
}

void UniverseElement::setSector(Sector* sector) {
    m_sector = sector;
}

bool UniverseElement::removalScheduled() const {
    return m_removalScheduled
}

void UniverseElement::scheduleRemoval() {
    m_removalScheduled = true;
}

void UniverseElement::update(float deltaSecs) {

}

