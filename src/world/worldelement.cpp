#include "worldelement.h"


WorldElement::WorldElement(World* world):
    m_world(world)
{
}

World* WorldElement::world() {
    return m_world;
}

bool WorldElement::activeInWorld() const {
    return m_active;
}

void WorldElement::activateInWorld() {
    m_active = true;
    onActivationInWorld();
}

void WorldElement::dectivateInWorld() {
    m_active = false;
    onDeactivationInWorld();
}

