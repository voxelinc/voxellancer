#include "worldelement.h"

#include <iostream>

#include "scripting/scriptengine.h"

#include "world/world.h"


WorldElement::WorldElement(World* world):
    m_world(world),
    m_active(false)
{
    activateInWorld();
}

WorldElement::~WorldElement() {
    if (m_active) {
        deactivateInWorld();
    }
}

World* WorldElement::world() {
    return m_world;
}

bool WorldElement::activeInWorld() const {
    return m_active;
}

void WorldElement::activateInWorld() {
    m_active = true;

    m_world->addElement(this);

    onActivationInWorld();
}

void WorldElement::deactivateInWorld() {
    m_active = false;

    HandleOwner::invalidate();

    onDeactivationInWorld();
}

void WorldElement::update(float deltaSec) {

}

void WorldElement::onActivationInWorld() {

}

void WorldElement::onDeactivationInWorld() {

}

